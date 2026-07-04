import pandas as pd
pd.plotting.register_matplotlib_converters()
import matplotlib.pyplot as plt
import seaborn as sns

example_filepath = "../input/example.csv"

example_data = pd.read_csv(example_filepath, index_col="Date", parse_dates=True)
# Set the width and height of the figure
plt.figure(figsize=(14,6))

plt.title("Example Title")

"""Trend"""
# line chart
sns.lineplot(data=example_data)
sns.lineplot(data=example_data['example_col'], label="example_col") # top-right corner label

plt.xlabel("Date")

"""Relationship"""
# bar chart
sns.barplot(x=example_data.index, y=example_data['example_col'])

plt.ylabel("Example y")

# heatmaps
sns.heatmap(data=example_data, annot=True) # annot=True display values

plt.xlabel("Example x")

# scatter(散点图)
sns.scatterplot(x=example_data['example_col'],y=example_data['example_row']) 
sns.regplot(x=example_data['example_col'],y=example_data['example_row']) # scatter plot with a regression line
sns.scatterplot(x=example_data['example_col'],y=example_data['example_row'],hue=example_data['type']) #  use different colors(hues) for different types
sns.lmplot(x='example_col',y='example_row',hue='type',data=example_data) # hue-scatter plot with regression lines 
sns.swarmplot(x=example_data['type'],y=example_data['example_row']) # categorical scatter plot

"""Distribution"""
# histogram
sns.histplot(example_data['example_col'])

# KDE(kernel density estimate) plot
sns.kdeplot(data=example_data['example_col'],shade=True)
# 2D KDE plot
sns.jointplot(x=example_data['example_col'],y=example_data['example_row'],kind="kde")

# color-coded plot
sns.histplot(data=example_data,x='example_col',hue='types')
sns.kdeplot(data=example_data,x='example_col',hue='types',shade=True)

"""seaborn Style"""
sns.set_style("dark") # darkgrid,whitegrid,dark,white,ticks(坐标轴刻度标记)