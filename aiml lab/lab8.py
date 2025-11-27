#EDA
import pandas as pd
import matplotlib.pyplot as plt

file_path="Student Data.xlsx"
df=pd.read_excel(file_path)

cols=["school","sex","age","address","famsize","Medu"]
df=df[cols]

print("First 10 rows:")
print(df.head(10),"\n")

print("Shape(rows,cols):",df.shape,"\n")

print("Missing values per column:")
print(df.isnull().sum(),"\n")

print("Mean:\n",df.mean(numeric_only=True),"\n")
print("Median:\n",df.median(numeric_only=True),"\n")
print("Mode:\n",df.mode().iloc[0],"\n")
print("Standard Deviation:\n",df.std(numeric_only=True),"\n")

print("Max values:\n",df.max(numeric_only=True),"\n")
print("Min values:\n",df.min(numeric_only=True),"\n")

print("Unique values per categorical column:")
print(df.select_dtypes(include=['object']).nunique(),"\n")

df['age'].plot(kind='hist',bins=10,edgecolor='black',title="Age Distribution")
plt.xlabel("Age")
plt.show()

df['sex'].value_counts().plot(kind='bar',title="Sex Frequency")
plt.xlabel("Sex")
plt.ylabel("Count")
plt.show()

plt.scatter(df['age'],df['Medu'])
plt.xlabel("Age")
plt.ylabel("Medu (Mother's Education)")
plt.title("Scatter plot: Age vs Medu")
plt.show()

df['age'].plot(kind='box',title="Boxplot of Age")
plt.show()
