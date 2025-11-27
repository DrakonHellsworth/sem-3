# K-Means Clustering without sklearn + Visualization
import pandas as pd
import numpy as np
import random
import matplotlib.pyplot as plt

random.seed(69)
df=pd.read_excel("e:/sem 3/aiml lab/cluster_data.xlsx")
print("Dataset:\n",df)

x=df[["dim1","dim2"]].values

def kmeans(x,k,i=100):
    c=x[random.sample(range(len(x)),k)]
    for _ in range(i):
        l=[]
        for p in x:
            dists=[]
            for ci in c:
                d=((p[0]-ci[0])**2+(p[1]-ci[1])**2)**0.5
                dists.append(d)
            min_idx=0
            for j in range(1,len(dists)):
                if dists[j] < dists[min_idx]:
                    min_idx=j
            l.append(min_idx)
        nc=[]
        for j in range(k):
            pts=[x[m] for m in range(len(x)) if l[m]==j]
            if pts:
                nc.append(np.mean(pts,axis=0))
            else:
                nc.append(c[j])
        if np.allclose(c,nc):
            break
        c=nc
    return c,l

k=3
centers,labels=kmeans(x,k)
df["Cluster"]=[l+1 for l in labels]

print("\nCluster Centers:\n",centers)
print("\nClustered Dataset:\n",df)
df.to_csv("clustered_data.csv")
print("\nExported to clustered_data.csv")

plt.figure(figsize=(8,6))
for j in range(k):
    pts=df[df["Cluster"]==j+1]
    plt.scatter(pts["dim1"],pts["dim2"],label=f"Cluster {j+1}",s=40)

centers=np.array(centers)
plt.scatter(centers[:,0],centers[:,1],c="black",marker="X",s=200,label="Centers")

plt.title("K-Means Clustering (k={k})")
plt.xlabel("dim1")
plt.ylabel("dim2")
plt.legend()
plt.grid(True,alpha=0.3)
plt.show()
