"""
loss function:MAE,MSE(Mean Square Error),Huber loss
optimizer:stochastic gradient descent(SGD)
iteration:minibatch(batch),complete round number:epoch -> batch_size * epochs
adam:self-tuning learning rate
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import make_column_transformer, make_column_selector
from sklearn.model_selection import train_test_split

fuel = pd.read_csv('../input/dl-course-data/fuel.csv')

X = fuel.copy()
# Remove target
y = X.pop('FE')

preprocessor = make_column_transformer(
    (StandardScaler(),
     make_column_selector(dtype_include=np.number)),
    (OneHotEncoder(sparse=False),
     make_column_selector(dtype_include=object)),
)

X = preprocessor.fit_transform(X)
y = np.log(y) # log transform target instead of standardizing

input_shape = [X.shape[1]]
print("Input shape: {}".format(input_shape))

from tensorflow import keras
from tensorflow.keras import layers

model = keras.Sequential([
    layers.Dense(128, activation='relu', input_shape=input_shape),
    layers.Dense(128, activation='relu'),    
    layers.Dense(64, activation='relu'),
    layers.Dense(1),
])

model.compile(
    optimizer = 'adam',
    loss = 'mae',
)

history = model.fit(
    X,y,
    batch_size=128,
    epochs=200
)

"""
history = model.fit(
    X_train, y_train,
    validation_data=(X_valid, y_valid),
    batch_size=256,
    epochs=10,
)
"""

import pandas as pd

history_df = pd.DataFrame(history.history)
# Start the plot at epoch 5. You can change this to get a different view.
history_df.loc[5:, ['loss']].plot();

"""
smaller batch size(data sample) -> noisier
learning rate -> speed
"""

"""
overfitting过拟合,underfitting欠拟合
"""

from tensorflow.keras import callbacks

early_stopping = callbacks.EarlyStopping(
    min_delta=0.001, # minimium amount of change to count as an improvement
    patience=5, # how many epochs to wait before stopping
    restore_best_weights=True,
)

history = model.fit(
    X, y,
    batch_size=512,
    epochs=50,
    callbacks=[early_stopping]
)

"""
dropout:randomly(parameter p) drop out some fraction of a layer's input units every step of training, 
making it much harder for the network to learn those spurious patterns in the training data.
batchnorm(BN):A batch normalization layer looks at each batch as it comes in, 
first normalizing the batch with its own mean and standard deviation, 
and then also putting the data on a new scale with two trainable rescaling parameters. 
Batchnorm, in effect, performs a kind of coordinated rescaling of its inputs.
标准化后的数据分布更稳定，使得梯度更新更平滑，允许使用更大的学习率。
减少对参数初始化的依赖，使得训练更加鲁棒。
防止激活值过大或过小，从而避免梯度消失(ReLU导致的训练停滞)或爆炸。
"""

model = keras.Sequential([
    layers.Dense(128, activation='relu', input_shape=input_shape),
    layers.Dropout(rate=0.3),
    layers.Dense(64, activation='relu'),
    layers.Dropout(rate=0.3),
    layers.Dense(1)
])
"""
the validation loss remains near a constant minimum even though the training loss continues to decrease. 
So we can see that adding dropout did prevent overfitting this time.
Moreover, by making it harder for the network to fit spurious patterns, 
dropout may have encouraged the network to seek out more of the true patterns, 
possibly improving the validation loss some as well
"""

model = keras.Sequential([
    layers.BatchNormalization(input_shape=input_shape),
    layers.Dense(512, activation='relu', input_shape=input_shape),
    layers.BatchNormalization(),
    layers.Dense(512, activation='relu'),
    layers.BatchNormalization(),
    layers.Dense(512, activation='relu'),
    layers.BatchNormalization(),
    layers.Dense(1),
])