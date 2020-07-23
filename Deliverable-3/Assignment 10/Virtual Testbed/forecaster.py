from scipy.stats import norm
import statsmodels.api as sm
import pickle
import sys
import os
import json
from time import time
import pandas as pd
from datetime import datetime

if len(sys.argv) == 3:
	fHorizon = int(sys.argv[1])
	fModelFile = sys.argv[2]

	ts = int(time())
	ts = ts + (fHorizon * 60)

	res = pickle.load( open( fModelFile, "rb" ) )
	prediction = res.predict(ts)