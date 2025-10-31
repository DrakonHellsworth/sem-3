import numpy as np
import pandas as pd

data=np.array([[2,3],[3,4],[4,5],[5,6]])
df=pd.DataFrame(data,columns=['X','Y'])
print("Original Data:\n",df)

X_mean=np.mean(data,axis=0)
X_std=np.std(data,axis=0)
X_sc=(data-X_mean)/X_std
print("\nStandardized Data:\n",X_sc)

cov_mat=np.cov(X_sc.T)
print("\nCovariance Matrix:\n",cov_mat)

eig_vals,eig_vecs=np.linalg.eig(cov_mat)
print("\nEigenvalues:\n",eig_vals)
print("\nEigenvectors (Principal Axes):\n",eig_vecs)

idx=np.argsort(eig_vals)[::-1]
eig_vals=eig_vals[idx]
eig_vecs=eig_vecs[:,idx]

first_axis=eig_vecs[:,0]
projection=np.dot(X_sc,first_axis)
print("\nProjection along first principal axis:\n",projection)

var_exp=eig_vals/np.sum(eig_vals)
print("\nExplained Variance Ratio:\n",var_exp)
