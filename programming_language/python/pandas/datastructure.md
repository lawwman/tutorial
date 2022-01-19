# Learning about Series and Dataframe in Pandas

Takeaways from reading pandas docs: https://pandas.pydata.org/pandas-docs/stable/user_guide/dsintro.html

## Series - 1D labelled array, hold any data type.
```python
pd.Series(['a', 'b', 'c', 'd'])  # series from list
pd.Series({0: 'a', 1: 'b', 2: 'c', 3: 'd'})  # series from dict

"""
0    a
1    b
2    c
3    d
dtype: object
"""
```
Simple ways to create a pandas series. when printed out. 0 to 3 are the indices. How can indices be used?
``` python
s = pd.Series(['a', 'b', 'c', 'd'])
s[0]  # a
s[1:]  # even slicing is possible.
"""
1    b       
2    c       
3    d       
dtype: object
"""
```
Above is a very ndarray-like way of accessing values. But a series is also dict-like.
- `0 in s` will return bool value
- `s.get(0, none)` similarly, dict .get() methods work too.

You can also do:
- `s + s`
- `s * 2`

which is exactly what you would expect. Output is the same series, but 2 times the value.

## Dataframe - 2D labelled array, hold any data type.
A series is an array of labelled values. We call the labels: `index`. In the context of a table comprised of rows and columns, a series is basically a single column, with the `index` acting as a "row id" of sorts.

A dataframe is just a table with 1 or more columns. A 2D array. It could be:
- an array of labelled series
- an array of labelled dicts
- an array of labelled lists
- or just a mixture of the above

A dataframe is an array of labelled columns. We call the labels: `columns`. You can also think of it as a dict of series, since the series/columns are labelled.

## .head() and .tail()
Applies to both series and dataframes.
```python

```