import pandas as pd

df1 = pd.DataFrame({'lkey': ['foo', 'bar', 'baz', 'foo'], 'value': [1, 2, 3, 5]})
"""
    lkey value
0   foo      1
1   bar      2
2   baz      3
3   foo      5
"""
df2 = pd.DataFrame({'rkey': ['foo', 'bar', 'baz', 'foo'], 'value': [5, 6, 7, 8]})
"""
    rkey value
0   foo      5
1   bar      6
2   baz      7
3   foo      8
"""
print(df1.merge(df2))  # default is an inner join, and an exact row match
"""
  lkey  value rkey
0  foo      5  foo  <-- exact row match of df1[3] against df2[0]
"""

"""
What do I mean by 'exact match'? 
 - let condition A = (1st col of df1) == (1st col of df2)
 - let condition B = (2nd col of df1) == (2nd col of df2) and so on for as many cols we have
exact match is only when all conditions A, B ... are true. Thats why only 1 row was found.
"""
print(df1.merge(df2, on='value'))  # whatever column name used for 'on' args, it has to be present in both df. same result as above.

"""
lets say we don't want an exact match. we only want to merge to merge on the condition that first col matches.

but since the col names are different, we can use the 'left_on' and 'right_on' args. note that you can't use 'left on'
without using 'right_on'. df1.merge(df2, left_on='lkey') returns an error as 'right_on' is not used.
"""

print(df1.merge(df2, left_on='lkey', right_on='rkey'))  # inner join on the lkey == rkey
"""
  lkey  value_x rkey  value_y
0  foo        1  foo        5
1  foo        1  foo        8
2  foo        5  foo        5
3  foo        5  foo        8
4  bar        2  bar        6
5  baz        3  baz        7
"""

