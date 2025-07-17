import pandas as pd
pd.set_option("display.max_rows", 5)
reviews = pd.read_csv("../input/wine-reviews/winemag-data-130k-v2.csv", index_col=0)

from learntools.core import binder; binder.bind(globals())
from learntools.pandas.summary_functions_and_maps import *
print("Setup complete.")

reviews.head()

median_points = reviews.points.median()

countries = reviews.country.unique()

reviews_per_country = reviews.country.value_counts()

centered_price = reviews.price - reviews.price.mean()

bargain_idx = (reviews.points / reviews.price).idxmax() # the index of the maximum value
bargain_wine = reviews.loc[bargain_idx, 'title']

n_trop = reviews.description.map(lambda desc: "tropical" in desc).sum()
n_fruity = reviews.description.map(lambda desc: "fruity" in desc).sum()
descriptor_counts = pd.Series([n_trop,n_fruity],index=['tropical','fruity'])

def star(row):
    if row.country == 'Canada':
        return 3
    else:
        if row.points >= 95:
            return 3
        elif row.points < 85:
            return 1
        else:
            return 2
        
star_ratings = reviews.apply(star, axis='columns')
"""
0         2
1         2
         ..
129969    2
129970    2
Length: 129971, dtype: int64;
"""