import copy as cp
import numpy as np
from ctypes import cdll
from matplotlib.image import imread

import warnings
warnings.filterwarnings('ignore')

import blur

cat = imread("Images/cat.jpg")
row, column, channels = np.shape(cat)

blurred = blur.blur(cat, row, column, channels)

# https://stackoverflow.com/questions/145270/calling-c-c-from-python