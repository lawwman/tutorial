import pandas as pd


# Study of .shift() and date_range() method

df = pd.DataFrame({"Col1": [10, 20, 15, 30, 45],
                   "Col2": [13, 23, 18, 33, 48],
                   "Col3": [17, 27, 22, 37, 52]},
                   index=pd.date_range("2020-01-01", "2020-01-05"))

print(df.shift(periods=3))  # shift df down 3 rows. First 3 rows are NaN. df.shift(periods=3, fill_value=0) to set NaN as 0
"""
            Col1  Col2  Col3
2020-01-01   NaN   NaN   NaN
2020-01-02   NaN   NaN   NaN
2020-01-03   NaN   NaN   NaN
2020-01-04  10.0  13.0  17.0
2020-01-05  20.0  23.0  27.0
"""

print(df.shift(periods=-1))  # shift df up 1 row.

print(df.shift(periods=1, axis="columns"))  # shift df left 1 column

print(pd.date_range(start='01-01-2020', end='01-05-2020'))  # mm-dd-yyyy
# output: DatetimeIndex(['2020-01-01', '2020-01-02', '2020-01-03', '2020-01-04', '2020-01-05'], dtype='datetime64[ns]', freq='D')

print(pd.date_range(start="01-01-2020", periods=5))  # same result as above

print(pd.date_range(start="01-01-2020", periods=5, freq="M"))  # increments of months
# output: DatetimeIndex(['2020-01-31', '2020-02-29', '2020-03-31', '2020-04-30','2020-05-31'], dtype='datetime64[ns]', freq='M')  # Note that they are all month ends.

print(pd.date_range(start="01-01-2020", periods=3, freq="5D"))  # increments of 5 Days
# output: DatetimeIndex(['2020-01-01', '2020-01-06', '2020-01-11'], dtype='datetime64[ns]', freq='5D')

"""
For complete list of freq aliases
https://pandas.pydata.org/pandas-docs/stable/user_guide/timeseries.html#timeseries-offset-aliases
"""

# back to .shift() method. use "freq" argument to shift the index only
print(df.shift(periods=1, freq="D"))  # increment index by 1 day. values stay the same
"""
            Col1  Col2  Col3
2020-01-02    10    13    17
2020-01-03    20    23    27
2020-01-04    15    18    22
2020-01-05    30    33    37
2020-01-06    45    48    52
"""
