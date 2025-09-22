import matplotlib.pyplot as plt

x=[1,2,3,4,5]
y=[10,60,30,40,50]
plt.plot(x,y)
plt.title("Simple Line Graph")
plt.show()

plt.plot(x,y,marker='+',linestyle='--',color='b')
plt.title("Line Graph with + marker,dashed line,blue color")
plt.show()

plt.plot(x,y,marker='o',linestyle='-',color='g')
plt.title("Line Graph with o marker,solid line,green color")
plt.show()
plt.plot(x,y,marker='s',linestyle='-.',color='r')
plt.title("Line Graph with square marker,dash-dot line,red color")
plt.show()

plt.plot(x,y,marker='o',linestyle='--',color='m')
plt.xlabel("X-axis Label")
plt.ylabel("Y-axis Label")
plt.title("Line Graph with Labels and Title")
plt.legend(["Data Series"])
plt.show()

plt.plot(x,y,color='green',linewidth=2,linestyle='-')
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.title("Customized Plot",fontsize=14,color='blue')
plt.xlim(0,6)
plt.ylim(0,60)
plt.grid(color='blue',linestyle='--',linewidth=2)
plt.show()

plt.plot(x, y, label="Line Graph", color='purple')
plt.legend()
plt.title("Line Graph")
plt.show()

plt.bar(x,y,color='skyblue')
plt.title("Bar Chart")
plt.show()

data=[10,20,20,30,40,40,40,50]
plt.hist(data,bins=5,color='orange')
plt.title("Histogram")
plt.show()

plt.scatter(x,y,color='red',marker='x')
plt.title("Scatter Plot")
plt.show()

sizes=[25,35,20,20]
labels=['Category A','Category B','Category C','Category D']

plt.pie(sizes,labels=labels,autopct='%1.1f%%')
plt.title("Pie Chart")
plt.show()

fig,ax=plt.subplots(2,2)

ax[0,0].plot(x,y,color='black')
ax[0,0].set_title("Line Graph")

ax[0,1].bar(x,y,color='blue')
ax[0,1].set_title("Bar Chart")

ax[1,0].scatter(x,y,color='red',marker='x')
ax[1,0].set_title("Scatter Plot")

ax[1,1].pie(sizes,labels=labels,autopct='%1.1f%%')
ax[1,1].set_title("Pie Chart")

plt.tight_layout()
plt.show()

