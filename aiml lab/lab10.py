import pandas as pd

file=r"e:\sem 3\aiml lab\data2.xlsx" 
df=pd.read_excel(file)

print("\nOriginal Data:")
print(df)

cols=df.select_dtypes(include=['object']).columns
print("\nCategorical columns detected:",list(cols))

enc=pd.get_dummies(df,columns=cols,dtype=int)

for col in cols:
    enc.columns=[c.replace(f"{col}_","") for c in enc.columns]

future_cols=[c for c in enc.columns if c in df['Future Dream'].unique()]
enc['Future Dream']=enc[future_cols].apply(lambda x:x.tolist(),axis=1)

difficulty_cols=[c for c in enc.columns if c in df['Label'].unique()]
enc['Difficulty']=enc[difficulty_cols].apply(lambda x:x.tolist(),axis=1)

print("\nEncoded Data with Future Dream and Difficulty Lists:")
print(enc)

out_file="encoded_output.xlsx"
enc.to_excel(out_file,index=False)
print(f"\nOne-hot encoded data saved to: {out_file}")
