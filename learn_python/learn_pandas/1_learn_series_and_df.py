import pandas as pd

"""
Series - 1D labelled array, hold any data type. The labels are referred to as index
https://pandas.pydata.org/pandas-docs/stable/user_guide/dsintro.html

Dataframe = 2D labeled data struct (like a spreadsheet or sql table). Can also think of it as a dict of series
https://pandas.pydata.org/pandas-docs/stable/user_guide/dsintro.html
"""

def create_series(example_type):
    if example_type == 1:
        return pd.Series(['a', 'b', 'c', 'd'])  # 'a' is labelled by index 0, 'b' is labelled by index 1 etc
        """
        0    a
        1    b
        2    c
        3    d
        dtype: object
        """
        # If you want to set the labels yourself,  `pd.Series(['a', 'b', 'c', 'd'], index=[0, 1, 2, 3])` or `pd.Series({0: 'a', 1: 'b', 2: 'c', 3: 'd'})` works


def series_tricks():
    s = create_series(1)
    # Series is dict-like (dict-like ways of accessing values with 'keys' work too)
    print(s3['a'])  # a
    print(s3.get('a'))  # a
    print('a' in s3)  # True


def create_df():
    return pd.DataFrame(
        {
            "col1": [1, 2, 3],
            "col2": pd.Series([4, 5, 6])
        }
    )


def df_attributes():
    df = create_df()
    print(df.head())  # print up to first 5
    print(df.tail(2))  # print last 2
    print(df.shape)  # (3, 2)
    

    print(df.columns)  # Index(['col1', 'col2'], dtype='object')
    print(df.index)  # RangeIndex(start=0, stop=3, step=1)

    print(df['col1'])  # returns a series. think of df as a dict of series.
    print(df[['col1', 'col2']])  # returns a dataframe with the selected cols.

    print('col1' in df)  # we can search if cols exist in the data frame

df_attributes()
