import pandas as pd
import matplotlib.pyplot as plt
import sys


def GraphChart() :
	df = pd.read_csv(sys.argv[1])
	print(df.shape)
	print(df.iloc[0])
		#df.plot()
		



GraphChart()