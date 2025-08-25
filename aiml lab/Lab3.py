import pandas as pd
from sklearn.neighbors import KNeighborsClassifier

df=pd.read_excel("e:/sem 3/aiml lab/data.xlsx")
print("Dataset:\n",df)

t1=df[df["Class"].notnull()]
t2=df[df["Class"].isnull()]

x=t1[["Height","Weight"]]
y=t1["Class"]

neigh=KNeighborsClassifier(n_neighbors=5)
neigh.fit(x,y)

pred=neigh.predict(t2[["Height","Weight"]])
prob=neigh.predict_proba(t2[["Height","Weight"]])

print("\nTest rows:\n",t2[["Height","Weight"]])
print("\nPredicted Class:",pred) 
print("Probabilities:\n",prob)
