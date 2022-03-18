# Learning about Indexing and selecting in Pandas

Takeaways from reading pandas docs: https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html

> I find the documentation to be good enough. It is an easy read if the above basic data structures are understood well.

## []
Using labels:
- `series[index]` -> using the `index` label. selects value based on label.
- `dataframe[column]` -> using the `column` label. selects series based on its label.
- `series_or_dataframe[label1:label5]` -> slicing works!
- `series_or_dataframe[[label1, label2]]` -> you can provide an array as well!

Using position:
- `series[0]` -> using the index position of 0. selects value based on label.
- `dataframe[0]` -> using the index position of 0. selects series based on its position.
- `series_or_dataframe[0:2]` -> slicing works!
- `series_or_dataframe[[0, 5]]` -> you can provide an array as well!

Using booleans:
- `series_or_dataframe[[True, False]]` -> can provide array of booleans (length of array should match length of series / df)

```python
"""
e    a
f    b
g    c
h    d
dtype: object
"""
s = pd.Series(['a', 'b', 'c', 'd'], index=['e', 'f', 'g', 'h'])
print(s[0])  # returns 'a'
print(s['e'])  # returns 'a'
```

## .loc[] - label based indexing
*pandas provides a suite of methods in order to have purely label based indexing. This is a strict inclusion based protocol. Every label asked for must be in the index, or a KeyError will be raised.*
- `series.loc[index]` -> using the `index` label. selects value based on label.
- `dataframe.loc[column]` -> using the `column` label. selects series based on its label.
- `series_or_dataframe.loc[label1:label5]` -> slicing works!
- `series_or_dataframe.loc[[label1, label2]]` -> you can provide an array as well!
- `series_or_dataframe.loc[[True, Flase]]` -> can provide array of booleans (length of array should match length of series / df)

## .iloc[] - position based indexing
*pandas provides a suite of methods in order to get purely integer based indexing. The semantics follow closely Python and NumPy slicing. These are 0-based indexing. When slicing, the start bound is included, while the upper bound is excluded. Trying to use a non-integer, even a valid label will raise an IndexError.*
- `series.iloc[0]` -> using the index position of 0. selects value based on label.
- `dataframe.iloc[0]` -> using the index position of 0. selects series based on its position.
- `series_or_dataframe.iloc[0:2]` -> slicing works!
- `series_or_dataframe.iloc[[0, 5]]` -> you can provide an array as well!
- `series_or_dataframe.iloc[[True, Flase]]` -> can provide array of booleans (length of array should match length of series / df)