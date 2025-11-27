# MULTI-MODEL SENTIMENT + EMOTION PIPELINE
# pip install pandas nltk textblob transformers torch

import os
import numpy as np
import pandas as pd
import torch
from textblob import TextBlob
import nltk
from nltk.sentiment import SentimentIntensityAnalyzer
from transformers import pipeline

INPUT_CSV  = r"E:\sem 3\project\YT_Videos_Comments_100k_english_clean.csv"
OUTPUT_CSV = r"E:\sem 3\project\YT_Videos_Comments_100k_labeled.csv"
VIDEO_SUMMARY_CSV = r"E:\sem 3\project\per_video_emotions.csv"

MAX_ROWS = 20000
BATCH_SIZE = 32
MAX_LEN = 256

HF_SENT_MODEL   = "siebert/sentiment-roberta-large-english"
HF_EMO_CARDIFF  = "cardiffnlp/twitter-roberta-base-emotion"
HF_EMO_HARTMANN = "j-hartmann/emotion-english-distilroberta-base"

DEVICE = 0 if torch.cuda.is_available() else -1


def ensure_vader():
    try:
        _ = SentimentIntensityAnalyzer()
    except LookupError:
        nltk.download("vader_lexicon")
    return SentimentIntensityAnalyzer()


def chunk_list(lst, n):
    for i in range(0, len(lst), n):
        yield lst[i:i+n]


def add_vader(df):
    print("Running VADER sentiment...")
    sia = ensure_vader()
    sc = df["Comment (Actual)"].astype(str).apply(sia.polarity_scores)
    df["vader_compound"] = sc.apply(lambda d: d["compound"])
    def lab(x):
        if x >= 0.05:
            return "positive"
        elif x <= -0.05:
            return "negative"
        else:
            return "neutral"
    df["vader_label"] = df["vader_compound"].apply(lab)
    return df


def add_textblob(df):
    print("Running TextBlob sentiment...")
    def tb_sc(t):
        tb = TextBlob(str(t))
        return tb.sentiment.polarity, tb.sentiment.subjectivity
    vals = df["Comment (Actual)"].astype(str).apply(tb_sc)
    df["tb_polarity"] = vals.apply(lambda x: x[0])
    df["tb_subjectivity"] = vals.apply(lambda x: x[1])
    return df


def add_hf_sentiment(df):
    print("Running HF transformer sentiment:", HF_SENT_MODEL)
    clf = pipeline("sentiment-analysis", model=HF_SENT_MODEL,
                   device=DEVICE, truncation=True)

    txts = df["Comment (Actual)"].astype(str).tolist()
    labs, scs = [], []

    for ch in chunk_list(txts, BATCH_SIZE):
        out = clf(ch, truncation=True, max_length=MAX_LEN)
        for r in out:
            labs.append(r["label"])
            scs.append(float(r["score"]))

    df["hf_sent_label"] = labs
    df["hf_sent_score"] = scs
    return df


def add_emotion_model(df, model_name, pref):
    print("Running HF emotion model:", model_name, " (prefix:", pref, ")")
    emo = pipeline("text-classification", model=model_name,
                   return_all_scores=True, device=DEVICE,
                   truncation=True)

    txts = df["Comment (Actual)"].astype(str).tolist()

    first = emo(txts[:1], truncation=True, max_length=MAX_LEN)[0]
    labs = [d["label"] for d in first]

    sc_by_lab = {f"{pref}{l.lower()}": [] for l in labs}

    for ch in chunk_list(txts, BATCH_SIZE):
        outs = emo(ch, truncation=True, max_length=MAX_LEN)
        for res in outs:
            m = {d["label"]: float(d["score"]) for d in res}
            for l in labs:
                col = f"{pref}{l.lower()}"
                sc_by_lab[col].append(m.get(l, 0.0))

    for col, arr in sc_by_lab.items():
        df[col] = arr

    emo_cols = list(sc_by_lab.keys())
    def top_emo(row):
        sub = row[emo_cols]
        if sub.isna().all():
            return None
        return sub.idxmax()[len(pref):]
    df[f"{pref}top"] = df.apply(top_emo, axis=1)
    return df


def build_video_summary(df):
    print("Building per-video emotion summary...")
    emo_cols = [c for c in df.columns
                if (c.startswith("cardiff_") or c.startswith("hart_"))
                and not c.endswith("top")]

    emo_mean = df.groupby("Video ID")[emo_cols].mean()
    cnt = df.groupby("Video ID")["Comment (Actual)"].count()
    sm = emo_mean.join(cnt.rename("comment_count"))

    def top_vid(row, pref):
        cols = [c for c in row.index if c.startswith(pref)]
        if not cols:
            return None
        sub = row[cols]
        return sub.idxmax()[len(pref):]

    sm["cardiff_top_video"] = sm.apply(lambda r: top_vid(r, "cardiff_"), axis=1)
    sm["hart_top_video"] = sm.apply(lambda r: top_vid(r, "hart_"), axis=1)

    return sm.reset_index()


def main():
    if not os.path.exists(INPUT_CSV):
        print("ERROR: Input file not found:", INPUT_CSV)
        return

    print("Loading:", INPUT_CSV)
    df = pd.read_csv(INPUT_CSV, dtype=str, encoding="utf-8", on_bad_lines="skip")

    need = ["Video ID", "Video Title", "Comment (Actual)", "Comment Author", "Comment Time"]
    df = df[[c for c in need if c in df.columns]]

    if MAX_ROWS is not None and len(df) > MAX_ROWS:
        print(f"Using first {MAX_ROWS} rows for speed (change MAX_ROWS to None for full).")
        df = df.head(MAX_ROWS)

    print("Total comments to process:", len(df))

    df = add_vader(df)
    df = add_textblob(df)
    df = add_hf_sentiment(df)
    df = add_emotion_model(df, HF_EMO_CARDIFF,  "cardiff_")
    df = add_emotion_model(df, HF_EMO_HARTMANN, "hart_")

    print("Saving per-comment labeled CSV...")
    df.to_csv(OUTPUT_CSV, index=False, encoding="utf-8")
    print("Saved:", OUTPUT_CSV)

    vs = build_video_summary(df)
    vs.to_csv(VIDEO_SUMMARY_CSV, index=False, encoding="utf-8")
    print("Saved per-video emotion summary:", VIDEO_SUMMARY_CSV)
    print("All done")


if __name__ == "__main__":
    main()
