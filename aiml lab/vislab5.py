# K-Means Clustering with sklearn + Visualization
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

df=pd.read_excel("e:/sem 3/aiml lab/cluster_data.xlsx")
print("Dataset:\n",df)

x=df[["dim1","dim2"]].values

k=3
kmeans=KMeans(n_clusters=k,random_state=69)
labels=kmeans.fit_predict(x)
centers=kmeans.cluster_centers_

df["Cluster"]=[l+1 for l in labels]

print("\nCluster Centers:\n",centers)
print("\nClustered Dataset:\n",df)
df.to_csv("clustered_data.csv",index=False)
print("\nExported to clustered_data.csv")

plt.figure(figsize=(8,6))
for j in range(k):
    pts=df[df["Cluster"]==j+1]
    plt.scatter(pts["dim1"],pts["dim2"],label=f"Cluster {j+1}",s=40)

centers=np.array(centers)
plt.scatter(centers[:,0],centers[:,1],c="black",marker="X",s=200,label="Centers")

plt.title(f"K-Means Clustering (k={k})")
plt.xlabel("dim1")
plt.ylabel("dim2")
plt.legend()
plt.grid(True,alpha=0.3)
plt.show()
