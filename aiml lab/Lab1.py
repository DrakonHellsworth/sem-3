import pandas as pd

df=pd.read_excel("e:/sem 3/aiml lab/data.xlsx")
print("Dataset:\n",df)

a=df[df["Class"].isnull()].iloc[0]
b=df[df["Class"].notnull()]

b["Dist"]=((b["Height"]-a["Height"])**2+(b["Weight"]-a["Weight"])**2 )**0.5

sorted=b.sort_values("Dist")

k=3
neighbors=sorted.head(k)

prob=neighbors["Class"].mode()[0]
print("\nNearest neighbors:\n", neighbors[["Height","Weight","Class","Dist"]])
print("\nPredicted Class for missing row:",prob)
