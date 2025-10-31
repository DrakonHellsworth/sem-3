import numpy as np
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

data=np.array([[2,3],[3,4],[4,5],[5,6]])
df=pd.DataFrame(data,columns=['X','Y'])
print("Original Data:\n",df)

sc=StandardScaler()
X_sc=sc.fit_transform(df)

pca=PCA(n_components=2)
pca.fit(X_sc)
X_pca=pca.transform(X_sc)

print("\nPrincipal Axes (Components):\n",pca.components_)
print("\nExplained Variance Ratio:", pca.explained_variance_ratio_)
print("\nProjection of each point along first principal axis:\n", X_pca)
