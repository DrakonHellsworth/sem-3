from sklearn.neighbors import KNeighborsClassifier
x=[[0,0],[1,1],[2,2],[3,3]]
y=[0,0,1,1]
neigh=KNeighborsClassifier(n_neighbors=3)
neigh.fit(x,y)
print(neigh.predict([[1,1]]))
print(neigh.predict_proba([[1,1]]))