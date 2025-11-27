import pandas as pd
import regex as re

input_file  = r"E:\sem 3\project\YT_Videos_Comments_100k.csv"
output_file = r"E:\sem 3\project\YT_Videos_Comments_100k_english_clean.csv"

print("Loading dataset...")

df = pd.read_csv(
    input_file,
    dtype=str,
    encoding="utf-8",
    on_bad_lines="skip"
)

def is_english(text):
    if pd.isna(text):
        return False
    return bool(re.match(r"^[\p{Latin}\p{Punctuation}\p{Number}\s]+$", text))

def clean_comment(text):
    if pd.isna(text):
        return ""
    text = text.replace("\n", " ").replace("\r", " ")
    text = re.sub(r"http\S+|www\S+", "", text)  # remove URLs
    text = re.sub(r"[^\p{Latin}\p{Number}\p{Punctuation}\s]", "", text)  # remove emojis, Chinese, Hindi etc.
    return text.strip()

print("Cleaning comments...")

df["Comment (Actual)"] = df["Comment (Actual)"].astype(str).apply(clean_comment)

print("Removing non-English comments...")
df = df[df["Comment (Actual)"].apply(is_english)]

print("Removing empty rows...")
df = df[df["Comment (Actual)"].str.strip() != ""]

print("Saving output...")
df.to_csv(output_file, index=False, encoding="utf-8")

print("Done! Saved:", output_file)
