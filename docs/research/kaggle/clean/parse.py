from learntools.core import binder
binder.bind(globals())
from learntools.data_cleaning.ex3 import *
print("Setup Complete")

# modules we'll use
import pandas as pd
import numpy as np
import seaborn as sns
import datetime

# read in our data
earthquakes = pd.read_csv("../input/earthquake-database/database.csv")

# set seed for reproducibility
np.random.seed(0)

print(earthquakes['Date'].head())

date_lengths = earthquakes.Date.str.len()
date_lengths.value_counts()

indices = np.where([date_lengths == 24])[1]
print('Indices with corrupted data:', indices)
earthquakes.loc[indices]

earthquakes.loc[3378, "Date"] = "02/23/1975"
earthquakes.loc[7512, "Date"] = "04/28/1985"
earthquakes.loc[20650, "Date"] = "03/13/2011"
earthquakes['date_parsed']=pd.to_datetime(earthquakes['Date'],format="%m/%d/%Y")

#earthquakes['date_parsed']=pd.to_datetime(earthquakes['Date'],infer_datetime_format=True)
day_of_month_earthquakes = earthquakes['date_parsed'].dt.day

sns.distplot(day_of_month_earthquakes, kde=False, bins=31)\



volcanos = pd.read_csv("../input/volcanic-eruptions/database.csv")

def parse_eruption_year(eruption_str):
    if eruption_str == 'Unknown':
        return np.nan
    elif 'BCE' in eruption_str:
        year=int(eruption_str.split()[0])
        return -year
    elif 'CE' in eruption_str:
        year=int(eruption_str.split()[0])
        return year
    else:
        return np.nan

volcanos['Eruption_year']=volcanos['Last Known Eruption'].apply(parse_eruption_year)
volcanos['Eruption_year']=volcanos['Eruption_year'].astype('Int64') #not int64
volcanos[['Last Known Eruption','Eruption_year']].sample(20)