# data clean + tag extract (core pipeline)
import pandas as pd, re, yake, spacy, csv
from nltk.stem import WordNetLemmatizer
from nltk.corpus import stopwords

nlp=spacy.load("en_core_web_sm")
lm=WordNetLemmatizer()
sw=set(stopwords.words("english"))

def clean(t):
    t=str(t).lower()
    t=re.sub(r'\[.*?\]|https?://\S+',' ',t)
    t=re.sub(r'[^a-z0-9\s\.]', ' ', t)
    t=re.sub(r'\s+',' ',t)
    return " ".join(lm.lemmatize(w) for w in t.split() if w not in sw)

# load dataset (any user-provided dataset)
df=pd.read_csv("dataset/raw.csv")
df["clean"]=df["text"].astype(str).apply(clean)

# tag extraction
ke=yake.KeywordExtractor(lan="en",n=3,top=20)
tags=[]
for t in df["clean"]:
    k=[w for w,s in ke.extract_keywords(t)]
    d=nlp(" ".join(t.split()[:400]))
    nc=[c.text for c in d.noun_chunks if len(c.text.split())>1]
    tags.append(list(dict.fromkeys(k+nc)))

df["tags"]=tags

# save processed outputs
df.to_csv("dataset/clean_processed.csv",index=False)

with open("dataset/tag_output.csv","w",newline='',encoding="utf-8") as f:
    w=csv.writer(f); w.writerow(["id","tags"])
    for i,r in df.iterrows(): w.writerow([i,"|".join(r["tags"])])
