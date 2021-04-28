import copy as cp
import numpy as np
from ctypes import cdll
from PIL import Image
from matplotlib.image import imread

import warnings
warnings.filterwarnings('ignore')

from blur import blur

img = imread("Images/loin.jpg").tolist()

blurred = blur(img)
blurred = np.array(blurred, dtype=np.uint8)

img = Image.fromarray(blurred, 'RGB')
img.save('Output/blurred_loin.png')
img.show()

# Helping Hand:
# https://stackoverflow.com/questions/145270/calling-c-c-from-python

# Commands:
# g++ -c -fPIC blur.cpp
# swig -c++ -python blur.i
# g++ -c -fPIC blur_wrap.cxx  -I/usr/include/python3.9 -I/usr/lib/python3.9
# g++ -shared -Wl,-soname,_blur.so -o _blur.so blur.o blur_wrap.o

# Cover Input:
# img = [[[135, 131, 119], [135, 131, 119], [135, 131, 119]],
# [[112, 109,  94], [111, 108,  93], [111, 108,  93]],
# [[136, 132, 120], [136, 132, 120], [136, 132, 120]]]