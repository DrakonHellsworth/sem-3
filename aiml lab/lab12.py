import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

f=r"e:\sem 3\aiml lab\creditcard.csv"
df=pd.read_csv(f)
print("Data loaded:",df.shape)

n=df['Class'].nunique()
print("No. of classes:",n)

c=df['Class'].value_counts()
print("Samples per class:\n",c)

if c.nunique()!=1:
    print("Unbalanced...balancing")
    maj=df[df['Class']==c.idxmax()]
    mino=df[df['Class']==c.idxmin()]
    mino_up=mino.sample(len(maj),replace=True,random_state=0)
    dfb=pd.concat([maj,mino_up],axis=0).sample(frac=1,random_state=0)
    print("Balanced counts:\n",dfb['Class'].value_counts())
else:
    print("Already balanced")

dfb.to_csv("balanced_creditcard.csv",index=False)
print("Saved: balanced_creditcard.csv")

x=dfb.drop('Class',axis=1)
y=dfb['Class']
xtr,xts,ytr,yts=train_test_split(x,y,test_size=0.3,random_state=0)

ep=10
r=[]
for i in range(ep):
    it=(i+1)*50
    m=LogisticRegression(max_iter=it,solver='lbfgs')
    m.fit(xtr,ytr)
    yp=m.predict(xts)
    acc=accuracy_score(yts,yp)
    pre=precision_score(yts,yp)
    rec=recall_score(yts,yp)
    f1=f1_score(yts,yp)
    r.append([i+1,it,acc,pre,rec,f1])

res=pd.DataFrame(r,columns=['Epoch','Iter','Accuracy','Precision','Recall','F1'])
print("\nResults:\n",res)

best=res.loc[res['F1'].idxmax()]
print(f"\nBest Epoch: {int(best['Epoch'])} | Acc={best['Accuracy']:.4f} | Pre={best['Precision']:.4f} | Rec={best['Recall']:.4f} | F1={best['F1']:.4f}")
