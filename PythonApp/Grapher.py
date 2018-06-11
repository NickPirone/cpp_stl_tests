import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys

def normalize_series(dframe, series_col_index) :
	y = dframe[series_col_index]
	log_y = np.log(y)
	diff_log_y = log_y - np.average(log_y)
	var_log_y = sum( diff_log_y ** 2 ) / len(y)
	stdev_log_y = np.sqrt(var_log_y)
	cnt = 0
	for i in range(0, len(log_y)) :
		if( abs(diff_log_y[i]) > (2*stdev_log_y) ):
			cnt += 1
			if(i > 5): 
				y.iloc[i] = y.iloc[i-1]
			else:
				y.iloc[i] = y.iloc[i+1]
	#print('cleaned:  ', cnt)

def add_moving_averages(dframe) :
	new_df = dframe.rolling(20).mean()
	return new_df

def graph_chart() :
	#we want to use this to read hte csv files, clean up the data, and then present a graph to the user.
	df = pd.read_csv(sys.argv[1]) #index_col=0
	for i in range(1, len(df.columns)): #only want to normalize the non-x series.
		normalize_series(df, df.columns[i])
	df = add_moving_averages(df)
	df.plot(kind='line', x='n',title=sys.argv[1])
	plt.show()

graph_chart()