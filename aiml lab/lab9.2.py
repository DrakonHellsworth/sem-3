import pandas as pd
import numpy as np

file_path="Student Data.xlsx"
df=pd.read_excel(file_path)

num_cols=df.select_dtypes(include=['number']).columns

z=(df[num_cols]-df[num_cols].mean())/df[num_cols].std()

threshold=2

outliers_colwise={}

for col in num_cols:
    mask=np.abs(z[col])>threshold
    outliers_colwise[col]=df.loc[mask,[col]]

for col,vals in outliers_colwise.items():
    print(f"\n{col}:{len(vals)} outliers")
    if len(vals)>0:
        print(vals.to_string(index=False))
    else:
        print("No outliers detected.")