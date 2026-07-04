"""
layers:any kind of data transformation
activation function:rectifier function:max(0,x) -> rectified linear unit(ReLU) -> max(0,w * x + b) 分段处理
inputs -> hidden -> hidden -> linear -> output
"""
import pandas as pd

concrete = pd.read_csv('../input/dl-course-data/concrete.csv')
concrete.head()

from tensorflow import keras
from tensorflow.keras import layers

model = keras.Sequential([
    # the hidden ReLU layers
    layers.Dense(units=512,activation='relu', input_shape=[8]),
    layers.Dense(units=512,activation='relu'),
    layers.Dense(units=512,activation='relu'),
    # the linear output layer 
    layers.Dense(units=1),
])
"""
model = keras.Sequential([
    layers.Dense(32, input_shape=[8]),
    layers.Activation('relu'),
    layers.Dense(32),
    layers.Activation('relu'),
    layers.Dense(1),
])
"""