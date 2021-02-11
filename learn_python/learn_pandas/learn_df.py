import pandas as pd

"""
Dataframe = 2D labeled data struct (like a spreadsheet or sql table). Can also think of it as a dict of series
https://pandas.pydata.org/pandas-docs/stable/user_guide/dsintro.html
"""
d = {
    "numbers": pd.Series([1, 2, 3, 4, 5]),
    "strings": pd.Series(['a', 'b', 'c', 'd', 'e']),
    "from_list": [6, 7, 8, 9, 10]  # list works too
}  # dict of series / list

df = pd.DataFrame(d)
print(df)
"""
   numbers strings  from_list
0        1       a          6
1        2       b          7
2        3       c          8
3        4       d          9
4        5       e         10
"""
print(df.columns)  # Index(['numbers', 'strings', 'from_list'], dtype='object')
print(df.index)  # RangeIndex(start=0, stop=5, step=1)

d2 = [
    {"col1": 1, "col2": 2, "col3": 3},
    {"col1": 4, "col2": 5, "col3": 6}
]  # list of dicts

df2 = pd.DataFrame(d2)
print(df2)

print(df2['col1'])  # returns a series. think of df as a dict of series.

print(df2[['col1', 'col2']])  # returns a dataframe with the selected cols.

d3 = {
    "index1": {"col1": 1, "col2": 2},
    "index2": {"col1": 3, "col2": 4},
}  # dict of dicts
df3 = pd.DataFrame.from_dict(d3, orient='index')
# orient means that the keys of the dict should be indexes. if orient is columns, then the keys are columns
print(df3)
"""
        col1  col2
index1     1     2
index2     3     4
"""
print(pd.DataFrame.from_dict(d3, orient='columns'))
"""
      index1  index2
col1       1       3
col2       2       4
"""

print('col1' in df3)  # we can search if cols exist in the data frame