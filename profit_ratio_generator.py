# -*- coding:utf-8 -*-

import os
import pandas as pd

filepath = os.getcwd() + "\\sp500_AdjClose.xlsx"

xls = pd.ExcelFile(filepath)

df = xls.parse('Sheet1')

df.

a = 0