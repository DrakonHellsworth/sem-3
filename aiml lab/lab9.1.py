#Z-Score
import pandas as pd
import numpy as np

file_path ="Student Data.xlsx"
df=pd.read_excel(file_path)

num_cols=df.select_dtypes(include=['number']).columns

z=(df[num_cols]-df[num_cols].mean())/df[num_cols].std()

threshold=2

outliers_mask=(np.abs(z)>threshold).any(axis=1)

outliers=df[outliers_mask]

print("Numeric Columns:", list(num_cols),"\n")
print("Total Rows:",len(df))
print("Outlier Rows Detected:", outliers.shape[0],"\n")

print("Outlier Data Points:")
print(outliers)
