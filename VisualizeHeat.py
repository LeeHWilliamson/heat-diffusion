import math as math
import matplotlib.colors as colors
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

csv_path = "C:\\Users\\Leeha\\projects\\heat diffusion\\heat-diffusion\\HeatGrid.csv"
df = pd.read_csv("C:\\Users\\Leeha\\projects\\heat diffusion\\heat-diffusion\\HeatGrid.csv" , index_col = 0)

plt.imshow(df, cmap = "hot", interpolation = "nearest")

plt.show()