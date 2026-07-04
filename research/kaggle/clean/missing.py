from learntools.core import binder
binder.bind(globals())
from learntools.data_cleaning.ex1 import *
print("Setup Complete")

# modules we'll use
import pandas as pd
import numpy as np

# read in all our data
sf_permits = pd.read_csv("../input/building-permit-applications-data/Building_Permits.csv")

# set seed for reproducibility
np.random.seed(0) 

sf_permits.head()

total_cell = np.product(sf_permits.shape)
missing_values_count = sf_permits.isnull().sum()
total_missing = missing_values_count.sum()
percent_missing = (total_missing / total_cell) * 100
print(percent_missing)

rows_with_na_droped = sf_permits.dropna()
rows_with_na_droped

sf_permits_with_na_dropped = sf_permits.dropna(axis=1)
dropped_columns = sf_permits.shape[1]-sf_permits_with_na_dropped.shape[1]

sf_permits_with_na_imputed = sf_permits.fillna(method='bfill',axis=0).fillna(0)
