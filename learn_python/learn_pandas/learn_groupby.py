import pandas as pd
import numpy as np

df = pd.DataFrame({'Animal': ['Falcon', 'Falcon', 'Parrot', 'Parrot'], 'Max Speed': [380., 370., 24., 26.]})
print(df)
"""
   Animal  Max Speed
0  Falcon      380.0
1  Falcon      370.0
2  Parrot       24.0
3  Parrot       26.0
"""

print(df.groupby(by=['Animal']).mean())
"""
        Max Speed
Animal           
Falcon      375.0
Parrot       25.0
"""

