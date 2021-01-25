import pandas as pd
import numpy as np

"""
https://pandas.pydata.org/pandas-docs/stable/user_guide/basics.html
"""

df = pd.DataFrame({'col1': list(range(0, 10))})  # create dataframe from 
# print(df.head())  # print first 5
# print(df.tail(3))  # print last 3
# print(df.shape)


df = pd.DataFrame(
    {
        "one": pd.Series([1, 2, 3], index=["a", "b", "c"]),  # only have first 3 cols
        "two": pd.Series([4, 5, 6 ,7], index=["a", "b", "c", "d"]),  # have all 4 cols
        "three": pd.Series([8, 9, 10], index=["b", "c", "d"]),  # only have last 3 cols
    }
)
# print(df)
"""
   one  two  three
a  1.0    4    NaN
b  2.0    5    8.0
c  3.0    6    9.0
d  NaN    7   10.0
"""

row = df.iloc[1]  # grab the 2nd row in the dataframe, i.e. 2nd item (index 'b') amongst all the columns: [2, 5, 8]
# print(df.sub(row, axis="columns"))  # 1st item used to subtract items in 1st col. # 2nd item used to subtract items in 2nd col.
"""
   one  two  three
a -1.0   -1    NaN
b  0.0    0    0.0
c  1.0    1    1.0
d  NaN    2    2.0
"""
column = df['one']  # grab everything in the column 'two'
# print(df.sub(column, axis="index"))  # 1st item used to subtract items in 1st row. # 2nd item used to subtract items in 2nd row.
"""
   one  two  three
a  0.0  3.0    NaN
b  0.0  3.0    6.0
c  0.0  3.0    6.0
d  NaN  NaN    NaN  <-- all NaN because first item is NaN, it is used to subtract items in row 'd'. number - NaN = NaN
"""
df = df.fillna(0)  # replace NaN with 0
# print(df.sub(df['one'], axis="index"))
"""
   one  two  three
a  0.0  3.0   -1.0
b  0.0  3.0    6.0
c  0.0  3.0    6.0
d  0.0  7.0   10.0
"""

df2 = pd.DataFrame(
    {
        "one": pd.Series([11, 12, 13], index=["a", "b", "c"]),  # only have first 3 cols
        "two": pd.Series([14, 15, 16 ,17], index=["a", "b", "c", "d"]),  # have all 4 cols
        "three": pd.Series([18, 19, 20], index=["b", "c", "d"]),  # only have last 3 cols
    }
)

# print(df.gt(df2))  # eq, ne, lt, gt, le, and ge
"""
     one    two  three
a  False  False  False
b  False  False  False
c  False  False  False
d  False  False  False
"""
