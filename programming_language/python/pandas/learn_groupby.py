import pandas as pd
# https://pandas.pydata.org/pandas-docs/stable/user_guide/groupby.html
# https://realpython.com/pandas-groupby/

simple_df = pd.DataFrame(
    {
        'Animal': ['Falcon', 'Falcon', 'Parrot', 'Parrot'], 
        'Max Speed': [380., 370., 24., 26.]
    }
)

simple_df2 = pd.DataFrame(
    {
        'Movement': ['Fly', 'Fly', 'Fly', 'Fly', 'Gallop', 'Gallop'],
        'Animal': ['Falcon', 'Falcon', 'Parrot', 'Parrot', 'Horse', 'Donkey'], 
        'Max Speed': [380., 370., 24., 26., 30., 15.]
    }
)

freq_df = pd.DataFrame(
   {
       "ID": [0, 1, 2, 3],
        "Price": [10, 20, 30, 40],
       "Publish date": [
            pd.Timestamp("2000-01-01 00:00:00+08"),
            pd.Timestamp("2000-01-01 00:07:00+08"),
            pd.Timestamp("2000-01-01 00:13:00+08"),
            pd.Timestamp("2000-01-01 00:26:00+08")
        ]
    }
)

freq_df2 = pd.DataFrame(
   {
       "ID": [0, 0, 0, 1, 1, 1],
       "Publish date": [
            pd.Timestamp("2000-01-01 00:00:00+08"),
            pd.Timestamp("2000-01-01 00:07:00+08"),
            pd.Timestamp("2000-01-01 00:26:00+08"),
            pd.Timestamp("2000-01-01 01:00:00+08"),
            pd.Timestamp("2000-01-01 01:07:00+08"),
            pd.Timestamp("2000-01-01 01:26:00+08")
        ]
    }
)

def simple_groupby_example():
    df = simple_df.copy(deep=True)
    df1 = df.groupby('Animal').mean()
    print(df1)
    #         Max Speed
    # Animal           
    # Falcon      375.0
    # Parrot       25.0

    # NOTE: 'Animal' column is now the new index. Can verify with print(df1.index)
    # We can disable this with `as_index=False`.
    df2 = df.groupby('Animal', as_index=False).mean()  # 'Animal' column is not index. their iloc position is index.
    print(df2)
    #     Animal  Max Speed
    # 0  Falcon      375.0
    # 1  Parrot       25.0


def simple_groupby_example2():
    df = simple_df2.copy(deep=True)
    df1 = df.groupby(['Animal', 'Movement']).mean()
    print(df1)
    print(df1.index)
    #                     Max Speed
    # Animal Movement           
    # Donkey Gallop         15.0
    # Falcon Fly           375.0
    # Horse  Gallop         30.0
    # Parrot Fly            25.0
    # NOTE: 'Animal' and 'Movement' are now columns.


def groupby_obj_attributes():
    df = simple_df.copy(deep=True)
    groupby_obj = df.groupby(pd.Grouper(key='Animal'))  # returns a groupby object

    print(groupby_obj.groups)  # {'Falcon': [0, 1], 'Parrot': [2, 3]}
    print(len(groupby_obj))  # return length of `.groups` dict. ans: 2


def simple_grouper_example():
    df = simple_df.copy(deep=True)
    groupby_obj = df.groupby(pd.Grouper(key='Animal'))  # returns a groupby object
    df1 = groupby_obj.mean()  # performs a function, and returns a dataframe
    print(df1)


def simple_grouper_freq_example():
    df = freq_df.copy(deep=True)
    df1 = df.groupby(pd.Grouper(key="Publish date", freq="5 min")).max()
    # print(df1)
    #                                 ID  Price
    # Publish date                         
    # 2000-01-01 00:00:00+08:00  0.0   10.0
    # 2000-01-01 00:05:00+08:00  1.0   20.0
    # 2000-01-01 00:10:00+08:00  2.0   30.0
    # 2000-01-01 00:15:00+08:00  NaN    NaN
    # 2000-01-01 00:20:00+08:00  NaN    NaN
    # 2000-01-01 00:25:00+08:00  3.0   40.0

    # NOTE: Behavior I observe: NaN objects are added to fill in the gap, ensuring 5 min windows.
    # This Behavior is only present when the first index is 'Publish date'. 
    # If we group by "ID" column first, the gaps are allowed.
    # groupby(["ID", pd.Grouper(key="Publish date", freq="5 min")]).

    df = freq_df2.copy(deep=True)
    df2 = df.groupby(["ID", pd.Grouper(key="Publish date", freq="5 min")]).max()
    # print(df2)
    #                                             Publish date
    # ID Publish date                                       
    # 0  2000-01-01 00:00:00+08:00   2000-01-01 00:00:00+08:00
    #    2000-01-01 00:05:00+08:00   2000-01-01 00:07:00+08:00
    #    2000-01-01 00:25:00+08:00   2000-01-01 00:26:00+08:00
    # 1  2000-01-01 01:00:00+08:00   2000-01-01 01:00:00+08:00
    #    2000-01-01 01:05:00+08:00   2000-01-01 01:07:00+08:00
    #    2000-01-01 01:25:00+08:00   2000-01-01 01:26:00+08:00

    # NOTE: 'Publish date' is used again for col values. df2 only has 'ID' and 'Publish date' columns.
    # Because both are used as MultiIndex, 'Publish date' is used again. If df2 has another column, that
    # column will be used instead.


df = pd.DataFrame(
    {
        'Movement': ['Fly', 'Fly', 'Fly', 'Fly', 'Gallop', 'Gallop'],
        'Max Speed': [380., 370., 24., 26., 30., 15.],
        'Min Speed': [1., 2., 3., 4., 5., 6.],
        'Animal': ['Falcon', 'Falcon', 'Parrot', 'Parrot', 'Horse', 'Donkey'], 
    }
)
s = pd.Series(['a', 'b', 'c', 'd'], index=['e', 'f', 'g', 'h'])  # series from list. Default index values.
# print(s)
print(s.loc[['e', 'g']])
# print(s['e'])