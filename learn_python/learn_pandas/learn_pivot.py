import pandas as pd
import numpy as np

# Specifically, pd.pivot_table.

sample_df = pd.DataFrame(
    {
        'id': ['0', '1', '2', '3', '4', '5'],
        'name': ['Tom', 'Dick', 'Lisa', 'Mary', 'Harry', 'Lee'],
        'gender': ['Male', 'Male', 'Female', 'Female', 'Male', 'Male'],
        'age': ['old', 'young', 'old', 'young', 'old', 'old'],
        'grade': ['A', 'B', 'C', 'D', 'A', 'B'],
        'score': [80, 70, 60, 50, 85, 75]
    }
)


def pivot_table_examples():
    df = sample_df.copy(deep=True)
    pivoted_df = pd.pivot_table(df, index='id', values='score', columns='gender')
    print(pivoted_df)
    # gender  Female  Male
    # id                  
    # 0          NaN  80.0
    # 1          NaN  70.0
    # 2         60.0   NaN
    # 3         50.0   NaN
    # 4          NaN  85.0
    # 5          NaN  75.0

    pivoted_df = pd.pivot_table(df, index=['id', 'gender'], values='score', columns='grade')
    print(pivoted_df)
    # grade         A     B     C     D
    # id gender                        
    # 0  Male    80.0   NaN   NaN   NaN
    # 1  Male     NaN  70.0   NaN   NaN
    # 2  Female   NaN   NaN  60.0   NaN
    # 3  Female   NaN   NaN   NaN  50.0
    # 4  Male    85.0   NaN   NaN   NaN
    # 5  Male     NaN  75.0   NaN   NaN

    pivoted_df = pd.pivot_table(df, index='gender', values='score', columns='age', aggfunc=np.sum)
    print(pivoted_df)
    # age     old  young
    # gender            
    # Female   60     50
    # Male    240     70

    # NOTE: Default aggfunc is np.mean.

    pivoted_df = pd.pivot_table(df, index='gender', values='score', columns='age', aggfunc=[np.sum, np.min, np.max])
    print(pivoted_df)
    #         sum       amin       amax      
    # age     old young  old young  old young
    # gender                                 
    # Female   60    50   60    50   60    50
    # Male    240    70   75    70   85    70

    # NOTE: Works with list of funcs.

pivot_table_examples()