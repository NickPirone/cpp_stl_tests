import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys

def normalize_series(dframe, series_col_index) :
	#so we have the first column as n, and the series we are normalizing will be series_col_index.
	#in order to get rid of outliers, we are going to:
		#a.  do a regression of the series with respect to n, logn, and n^2.
		#b.  set outliers equal to their expected values.
	y_bar = np.average(dframe[series_col_index])
	print(y_bar)
	return 0




def graph_chart() :
	#we want to use this to read hte csv files, clean up the data, and then present a graph to the user.
	df = pd.read_csv(sys.argv[1]) #index_col=0
	df.insert(1, 'n_squared', np.square(df['n']))
	df.insert(2, 'log_n', np.log2(df['n']))
	for i in range(3, len(df.columns)): #only want to normalize the non-x series.
		normalize_series(df, df.columns[i])
	print(df.iloc[0:20])
	print(df.shape)
	print(df.iloc[0:2])
	df.plot(kind='line', x='n', y='n_squared')
	plt.show()


graph_chart()