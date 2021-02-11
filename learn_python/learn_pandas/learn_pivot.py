# import pandas as pd

# df = pd.DataFrame({
#     "lev1": [1, 1, 1, 2, 2, 2],
#     "lev2": [1, 1, 2, 1, 1, 2],
#     "lev3": [1, 2, 1, 2, 1, 2],
#     "lev4": [1, 2, 3, 4, 5, 6],
#     "values": [0, 1, 2, 3, 4, 5]})

# print(pd.pivot_table(df, index=['lev1', 'lev2'], values='values'))

# df = pd.pivot_table(df, index=['lev1', 'lev2'], values='values')
# df.to_csv('test.csv')

user = {'test': 1, 'test2': 2}

print(user['test3'])