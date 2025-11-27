import pandas as pd

d={"wt":[60,None,70,80,90,40],
   "ht":[170,180,190,None,160,165],
   "cl":["Normal","overweight",None,"Underweight",None,"Normal"]}

df=pd.DataFrame(d)

print("Rows:",df.shape[0])
print("Cols:",df.shape[1])
print("\nHead:\n",df.head())
print("\nSize:",df.size)
print("\nMissing:\n",df.isnull().sum())

n=df.select_dtypes(include='number')
print("\nSum:\n",n.sum())
print("\nAvg:\n",n.mean())
print("\nMin:\n",n.min())
print("\nMax:\n",n.max())

m={"Normal":"N","overweight":"O","Underweight":"U"}
df['cl'] = df['cl'].map(m).fillna("Ukn")

feat=df[['wt','ht']].values.tolist()
label=df['cl'].tolist()

print("\nFeatures:",feat)
print("Labels:",label)

df.to_csv("exp.csv")
print("\nExported to exp.csv")