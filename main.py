import copy as cp
import numpy as np
from ctypes import cdll
from PIL import Image
from matplotlib.image import imread

import warnings
warnings.filterwarnings('ignore')

from gaussianBlur import GaussianBlur
from blur import blur
from grayscale import grayscale
from sobel import SobelOperator

def read_image(filename):
    return imread(filename).tolist()

def gaussian_blur(image, raduis=3):
    blurred = GaussianBlur(image, raduis)
    return np.array(blurred, dtype=np.uint8)

def to_grayscale(image):
    gray = grayscale(image)
    return np.array(gray, dtype=np.uint8)

def write_image(filename, image, format = 'RGB'):
    img = Image.fromarray(image, format)
    img.save(filename)

image = read_image('Images/random.jpeg')
gray_image = to_grayscale(image)
edges = SobelOperator(gray_image.tolist())
edges = np.array(edges, dtype=np.uint8)
write_image('Output/sobel_random.jpeg', edges, format='L')

# blurred_image = gaussian_blur(image, 5)

# write_image('Output/gray_random.jpeg', gray_image, format='L')
# write_image('Output/blurred_random.jpeg', blurred_image)


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