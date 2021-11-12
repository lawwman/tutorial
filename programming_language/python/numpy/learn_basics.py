import numpy as np 
  
np.where([[True, False], [True, True]], [[1, 2], [3, 4]], [[5, 6], [7, 8]])
print(np.where([[True, False], [True, True]], [[1, 2], [3, 4]], [[5, 6], [7, 8]]))

a = np.array([[1, 2, 3], [4, 5, 6]])
print(a)
print(a < 4)
print(np.where(a < 4))