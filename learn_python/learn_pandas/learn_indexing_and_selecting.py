import pandas as pd
import numpy as np

"""
https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html
"""

simple_df = pd.DataFrame(
    {
        'col1': list(range(0, 10)),
        'col2': list(range(0, 10)),
        'col3': list(range(0, 10)),
    }
)

print(type(simple_df))
some_value = simple_df.loc[0, "col1"]
print(type(some_value))

def df_attributes():
    df = simple_df.copy(deep=True)
    print(df.head())  # print first 5
    print(df.tail(3))  # print last 3
    print(df.shape)

