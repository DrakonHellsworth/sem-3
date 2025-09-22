import matplotlib.pyplot as plt

x=[1,2,3,4,5]
y=[10,60,30,40,50]
plt.plot(x, y)
plt.show()

plt.plot(x,y,marker='+',linestyle='--',color='b')
plt.show()

plt.plot(x,y)
plt.xlabel('X-axis Label')
plt.ylabel('Y-axis Label')
plt.title('Title of the Plot')
plt.legend(['Data Series'])
plt.show()

plt.grid(True)
plt.grid(color='blue',linestyle='--',linewidth=2)
plt.show()

plt.plot(x,y,color='green',linewidth=2,linestyle='-')
plt.xlim(0,6)
plt.ylim(0,60)
plt.title('Customized Plot',fontsize=14,color='blue')
plt.show()

plt.plot(x,y,label='Line Graph',color='purple')
plt.show()

plt.bar(x,y,color='skyblue')
plt.title('Bar Chart Example')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.show()

data=[10,20,20,30,40,40,40,50]
plt.hist(data,bins=5,color='orange')
plt.title('Histogram Example')
plt.xlabel('Value Ranges')
plt.ylabel('Frequency')
plt.show()

plt.scatter(x,y,color='red',marker='x')
plt.show()

sizes=[25,35,20,20]
labels=['Category A','Category B','Category C','Category D']
plt.pie(sizes,labels=labels,autopct='%1.1f%%')

fig,ax=plt.subplots(2, 2)
ax[0,0].plot(x,y)
ax[0,0].set_title('Line Graph')

ax[0,1].bar(x,y)
ax[0,1].set_title('Bar Chart')

ax[1,0].scatter(x,y)
ax[1,0].set_title('Scatter Plot')

ax[1,1].pie(sizes,labels=labels,autopct='%1.1f%%')
ax[1,1].set_title('Pie Chart')

plt.tight_layout()
plt.show()

fig,ax=plt.subplots(2,2)

ax[0,0].plot(x,y)
ax[0,0].set_title('Line Graph')
ax[0,0].set_xlabel('X Label 1',labelpad=10,fontsize=6,color='red')
ax[0,0].set_ylabel('Y Label 1',labelpad=10,fontsize=6,color='red')
ax[0,0].legend("Legend",loc="upper right")

ax[0,1].bar(x,y)
ax[0,1].set_title('Bar Chart')

ax[1,0].scatter(x,y)
ax[1,0].set_title('Scatter Plot')

ax[1,1].pie(sizes,labels=labels,autopct='%1.1f%%')
ax[1,1].set_title('Pie Chart')

plt.tight_layout()
plt.show()