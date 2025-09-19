#liner regression without sklearn
import numpy as np
import matplotlib.pyplot as plt

x=np.array([35,45,50,65,70,75],dtype=float)
y=np.array([2,3,4,5,6,7],dtype=float)

xm=np.mean(x)
ym=np.mean(y)

num=np.sum((x-xm)*(y-ym))
den=np.sum((x-xm)**2)
m=num/den
c=ym-m*xm

print(f"Slope (m):{m}")
print(f"Intercept (c):{c}")

yp=m*x+c
mse=np.mean((y-yp)**2)
print(f"Mean Squared Error:{mse}")
plt.scatter(x,y,color='blue',label='Data points')
plt.plot(x,yp,color='red',label='Regression line')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()