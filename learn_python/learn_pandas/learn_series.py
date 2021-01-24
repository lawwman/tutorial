import pandas as pd

"""
Series - 1D labelled array, hold any data type. The labels are referred to as index
https://pandas.pydata.org/pandas-docs/stable/user_guide/dsintro.html

The following are the stuff I think is useful
"""

s1 = pd.Series(['a', 'b', 'c', 'd'])  # 'a' is labelled by index 0, 'b' is labelled by index 1 etc
print(s1)
"""
0    a
1    b
2    c
3    d
dtype: object

Following 2 produces same results
 > pd.Series(['a', 'b', 'c', 'd'], index=[0, 1, 2, 3])
 > pd.Series({0: 'a', 1: 'b', 2: 'c', 3: 'd'})
"""

# first arg already has index. The values in data corresponding to the labels in the index will be pulled out.
s2 = pd.Series({0: 'a', 1: 'b', 2: 'c', 3: 'd'}, index=[0, 1, 2, 3, 4])
print(s2)
"""
0    a
1    b
2    c
3    d
4    NaN  <-- NaN (not a number) is the standard missing data marker used in pandas.
dtype: object
"""
print(s2[:2])  # slicing works
"""
0    a
1    b
dtype: object
"""
s3 = pd.Series(['a', 'b', 'c', 'd'], index=['a', 'b', 'c', 'd'])  # alphabetical index
print(s3[:2])  # index slicing even with non number index
"""
a    a
b    b
dtype: object
"""
print(s3[s3 == 'a'])  # can use conditions as well
"""
a    a
dtype: object
"""
# Series is dict-like (dict-like ways of accessing values with 'keys' work too)
print(s3['a'])  # a
print(s3.get('a'))  # a
print('a' in s3)  # True

s4 = pd.Series([1, 2, 3, 4])
print(s4 + s4)  # Vectorized operations with Series
"""
0    2
1    4
2    6
3    8
dtype: int64
"""
print(s4 * 3)
"""
0    3
1    6
2    9
3    12
dtype: int64
"""
