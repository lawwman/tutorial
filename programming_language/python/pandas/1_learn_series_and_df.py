import pandas as pd

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

