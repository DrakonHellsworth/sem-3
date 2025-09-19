# Linear regression with sklearn
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error

x=np.array([35,45,50,65,70,75],dtype=float).reshape(-1,1)
y=np.array([2,3,4,5,6,7],dtype=float)

model=LinearRegression()
model.fit(x, y)

m=model.coef_[0]
c=model.intercept_

print(f"Slope (m):{m}")
print(f"Intercept (c):{c}")

yp=model.predict(x)

mse=mean_squared_error(y, yp)
print(f"Mean Squared Error: {mse}")

plt.scatter(x, y, color='blue', label='Data points')
plt.plot(x, yp, color='red', label='Regression line')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Linear Regression with sklearn')
plt.legend()
plt.show()
