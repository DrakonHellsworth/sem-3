# MULTI-MODEL SENTIMENT + EMOTION PIPELINE
# ----------------------------------------
# Requires (run once):
# pip install pandas nltk textblob transformers torch

import os
import numpy as np
import pandas as pd
import torch
from textblob import TextBlob
import nltk
from nltk.sentiment import SentimentIntensityAnalyzer
from transformers import pipeline

# ==== CONFIG ====

# Path to your cleaned CSV (change if needed)
INPUT_CSV  = r"E:\sem 3\project\YT_Videos_Comments_100k_english_clean.csv"
# Per-comment labeled output
OUTPUT_CSV = r"E:\sem 3\project\YT_Videos_Comments_100k_labeled.csv"
# Per-video emotion summary
VIDEO_SUMMARY_CSV = r"E:\sem 3\project\per_video_emotions.csv"

# For speed while testing: limit rows (set None for ALL)
MAX_ROWS = 20000        # e.g. 20000; set to None when final

BATCH_SIZE = 32         # HF pipeline batch size
MAX_LEN = 256           # truncate long comments to 256 tokens

# HF model names
HF_SENT_MODEL   = "siebert/sentiment-roberta-large-english"
HF_EMO_CARDIFF  = "cardiffnlp/twitter-roberta-base-emotion"
HF_EMO_HARTMANN = "j-hartmann/emotion-english-distilroberta-base"

DEVICE = 0 if torch.cuda.is_available() else -1  # GPU if available, else CPU


# ==== UTILITIES ====

def ensure_vader():
    """Make sure VADER lexicon is available."""
    try:
        _ = SentimentIntensityAnalyzer()
    except LookupError:
        nltk.download("vader_lexicon")
    return SentimentIntensityAnalyzer()


def chunk_list(lst, size):
    """Yield chunks of a list."""
    for i in range(0, len(lst), size):
        yield lst[i:i+size]


def add_vader(df):
    print("Running VADER sentiment...")
    sia = ensure_vader()
    scores = df["Comment (Actual)"].astype(str).apply(sia.polarity_scores)
    df["vader_compound"] = scores.apply(lambda d: d["compound"])
    # Standard thresholds
    def vlab(x):
        if x >= 0.05:
            return "positive"
        elif x <= -0.05:
            return "negative"
        else:
            return "neutral"
    df["vader_label"] = df["vader_compound"].apply(vlab)
    return df


def add_textblob(df):
    print("Running TextBlob sentiment...")
    def tb_scores(t):
        tb = TextBlob(str(t))
        return tb.sentiment.polarity, tb.sentiment.subjectivity
    vals = df["Comment (Actual)"].astype(str).apply(tb_scores)
    df["tb_polarity"] = vals.apply(lambda x: x[0])
    df["tb_subjectivity"] = vals.apply(lambda x: x[1])
    return df


def add_hf_sentiment(df):
    print("Running HF transformer sentiment:", HF_SENT_MODEL)
    clf = pipeline("sentiment-analysis", model=HF_SENT_MODEL,
                   device=DEVICE, truncation=True)

    texts = df["Comment (Actual)"].astype(str).tolist()
    labels = []
    scores = []

    for chunk in chunk_list(texts, BATCH_SIZE):
        out = clf(chunk, truncation=True, max_length=MAX_LEN)
        for r in out:
            labels.append(r["label"])
            scores.append(float(r["score"]))

    df["hf_sent_label"] = labels
    df["hf_sent_score"] = scores
    return df


def add_emotion_model(df, model_name, prefix):
    """
    Run an emotion model with return_all_scores=True.
    prefix -> column prefix, e.g. 'cardiff_' or 'hart_'.
    Returns: df with added emotion probability columns + top label col.
    """
    print(f"Running HF emotion model: {model_name}  (prefix: {prefix})")
    emo_pipe = pipeline("text-classification", model=model_name,
                        return_all_scores=True, device=DEVICE,
                        truncation=True)

    texts = df["Comment (Actual)"].astype(str).tolist()
    all_results = []

    # First batch to discover label names (keeps code robust)
    first = emo_pipe(texts[:1], truncation=True, max_length=MAX_LEN)[0]
    labels = [d["label"] for d in first]

    # Prepare dict of label -> list of scores
    scores_by_label = {f"{prefix}{lab.lower()}": [] for lab in labels}

    # Process all chunks
    for chunk in chunk_list(texts, BATCH_SIZE):
        outs = emo_pipe(chunk, truncation=True, max_length=MAX_LEN)
        for res in outs:
            # res is list of {label, score}
            lbl2sc = {d["label"]: float(d["score"]) for d in res}
            for lab in labels:
                col = f"{prefix}{lab.lower()}"
                scores_by_label[col].append(lbl2sc.get(lab, 0.0))

    # Attach columns
    for col, arr in scores_by_label.items():
        df[col] = arr

    # Top emotion label per comment for this model
    emo_cols = list(scores_by_label.keys())
    def top_emo(row):
        sub = row[emo_cols]
        if sub.isna().all():
            return None
        return sub.idxmax()[len(prefix):]  # remove prefix

    df[f"{prefix}top"] = df.apply(top_emo, axis=1)
    return df


def build_video_summary(df):
    print("Building per-video emotion summary...")

    # All emotion columns from both models
    emo_cols = [c for c in df.columns
                if c.startswith("cardiff_") or c.startswith("hart_")]
    # Remove the "top" label columns from numeric aggregation
    emo_cols = [c for c in emo_cols if not c.endswith("top")]

    # Mean emotion scores per video
    emo_mean = df.groupby("Video ID")[emo_cols].mean()

    # Comment counts per video
    counts = df.groupby("Video ID")["Comment (Actual)"].count()
    summary = emo_mean.join(counts.rename("comment_count"))

    # Top emotion per video for each model (by average score)
    def top_per_video(row, prefix):
        cols = [c for c in row.index if c.startswith(prefix)]
        if not cols:
            return None
        sub = row[cols]
        return sub.idxmax()[len(prefix):]

    summary["cardiff_top_video"] = summary.apply(
        lambda r: top_per_video(r, "cardiff_"), axis=1
    )
    summary["hart_top_video"] = summary.apply(
        lambda r: top_per_video(r, "hart_"), axis=1
    )

    summary = summary.reset_index()
    return summary


# ==== MAIN ====

def main():
    if not os.path.exists(INPUT_CSV):
        print("ERROR: Input file not found:", INPUT_CSV)
        return

    print("Loading:", INPUT_CSV)
    df = pd.read_csv(INPUT_CSV, dtype=str, encoding="utf-8", on_bad_lines="skip")

    # Keep only needed columns (robust if some missing)
    needed = ["Video ID", "Video Title", "Comment (Actual)", "Comment Author", "Comment Time"]
    df = df[[c for c in needed if c in df.columns]]

    if MAX_ROWS is not None and len(df) > MAX_ROWS:
        print(f"Using first {MAX_ROWS} rows for speed (change MAX_ROWS to None for full).")
        df = df.head(MAX_ROWS)

    print("Total comments to process:", len(df))

    # 1) VADER
    df = add_vader(df)

    # 2) TextBlob
    df = add_textblob(df)

    # 3) HF sentiment transformer
    df = add_hf_sentiment(df)

    # 4) Cardiff emotion model
    df = add_emotion_model(df, HF_EMO_CARDIFF, prefix="cardiff_")

    # 5) Hartmann emotion model
    df = add_emotion_model(df, HF_EMO_HARTMANN, prefix="hart_")

    # Save full per-comment labeled dataset
    print("Saving per-comment labeled CSV...")
    df.to_csv(OUTPUT_CSV, index=False, encoding="utf-8")
    print("Saved:", OUTPUT_CSV)

    # Build per-video emotion summary
    vid_summary = build_video_summary(df)
    vid_summary.to_csv(VIDEO_SUMMARY_CSV, index=False, encoding="utf-8")
    print("Saved per-video emotion summary:", VIDEO_SUMMARY_CSV)

    print("All done ✅")


if __name__ == "__main__":
    main()
