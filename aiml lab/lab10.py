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

print("\nEncoded Data:")
print(enc)

out_file="encoded_output.xlsx"
enc.to_excel(out_file,index=False)
print(f"\nOne-hot encoded data saved to:{out_file}")
