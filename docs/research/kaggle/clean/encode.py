from learntools.core import binder
binder.bind(globals())
from learntools.data_cleaning.ex4 import *
print("Setup Complete")

# modules we'll use
import pandas as pd
import numpy as np

# helpful character encoding module
import charset_normalizer

# set seed for reproducibility
np.random.seed(0)

sample_entry = b'\xa7A\xa6n'
print(sample_entry)
print('data type:', type(sample_entry))
new_entry = sample_entry.decode("big5-tw").encode("utf-8")
print(new_entry)

# look at the first ten thousand bytes to guess the character encoding
with open("../input/fatal-police-shootings-in-the-us/PoliceKillingsUS.csv", 'rb') as rawdata:
    result = charset_normalizer.detect(rawdata.read(100000))

# check what the character encoding might be
print(result)
police_killings = pd.read_csv("../input/fatal-police-shootings-in-the-us/PoliceKillingsUS.csv",encoding='windows-1250')

police_killings.to_csv("my_file.csv")

#ftfy module