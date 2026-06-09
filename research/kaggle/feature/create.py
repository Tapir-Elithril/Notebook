from learntools.core import binder
binder.bind(globals())
from learntools.feature_engineering_new.ex3 import *

import numpy as np
import pandas as pd
from sklearn.model_selection import cross_val_score
from xgboost import XGBRegressor


def score_dataset(X, y, model=XGBRegressor()):
    # Label encoding for categoricals
    for colname in X.select_dtypes(["category", "object"]):
        X[colname], _ = X[colname].factorize()
    # Metric for Housing competition is RMSLE (Root Mean Squared Log Error)
    score = cross_val_score(
        model, X, y, cv=5, scoring="neg_mean_squared_log_error",
    )
    score = -1 * score.mean()
    score = np.sqrt(score)
    return score


# Prepare data
df = pd.read_csv("../input/fe-course-data/ames.csv")
X = df.copy()
y = X.pop("SalePrice")

"""Mathematical Transforms"""
X_1 = pd.DataFrame()  # dataframe to hold new features(Ctor)

X_1["LivLotRatio"] = df.GrLivArea / df.LotArea
X_1["Spaciousness"] = (df.FirstFlrSF + df.SecondFlrSF) / df.TotRmsAbvGrd
X_1["TotalOutsideSF"] = df.WoodDeckSF + df.OpenPorchSF + df.EnclosedPorch + df.Threeseasonporch + df.ScreenPorch

"""Categorical Interaction"""
X_2 = pd.DataFrame()
# One-hot encode BldgType. Use `prefix="Bldg"` in `get_dummies`
X_2 = pd.get_dummies(df.BldgType, prefix="Bldg")
# Multiply
X_2 = X_2.mul(df.GrLivArea, axis=0)

# Join the new features to the feature set
X = X.join(X_2)
"""
Categorical: ["A", "B", "A", "C"] (分类变量)
Continuous: [10, 20, 30, 40] (连续变量)
prefix = Cat
Cat_A  Cat_B  Cat_C
1      0      0
0      1      0
1      0      0
0      0      1
Cat_A  Cat_B  Cat_C
10     0      0
0      20     0
30     0      0
0      0      40
"""

"""Count"""
X_3 = pd.DataFrame()
porchtypes = ["WoodDeckSF", "OpenPorchSF", "EnclosedPorch", "Threeseasonporch", "ScreenPorch"]
X_3["PorchTypes"] = df[porchtypes].gt(0.0).sum(axis=1)

"""Break Down"""
X_4 = pd.DataFrame()
X_4["MSClass"] = df.MSSubClass.str.split("_",n=1,expand=True)[0] # n=1 for first "_" ,[0] for the first part([1] for the other)

"""Group"""
X_5 = pd.DataFrame()
X_5["MedNhbdArea"] = df.groupby("Neighborhood")["GrLivArea"].transform("median")