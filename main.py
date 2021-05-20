import numpy as np
import copy as cp
import numpy as np

from PIL import Image
from matplotlib.image import imread

import warnings
warnings.filterwarnings('ignore')

from gaussianBlur import GaussianBlur
from blur import blur
from grayscale import grayscale
from sobel import SobelOperator

def non_max_suppression(img, D):
    M, N = img.shape
    Z = np.zeros((M,N), dtype=np.int32)
    angle = D * 180. / np.pi
    angle[angle < 0] += 180

    
    for i in range(1,M-1):
        for j in range(1,N-1):
            try:
                q = 255
                r = 255
                
               #angle 0
                if (0 <= angle[i,j] < 22.5) or (157.5 <= angle[i,j] <= 180):
                    q = img[i, j+1]
                    r = img[i, j-1]
                #angle 45
                elif (22.5 <= angle[i,j] < 67.5):
                    q = img[i+1, j-1]
                    r = img[i-1, j+1]
                #angle 90
                elif (67.5 <= angle[i,j] < 112.5):
                    q = img[i+1, j]
                    r = img[i-1, j]
                #angle 135
                elif (112.5 <= angle[i,j] < 157.5):
                    q = img[i-1, j-1]
                    r = img[i+1, j+1]

                if (img[i,j] >= q) and (img[i,j] >= r):
                    Z[i,j] = img[i,j]
                else:
                    Z[i,j] = 0

            except IndexError as e:
                pass
    
    return Z

def read_image(filename):
    return imread(filename).tolist()

def write_image(filename, image, format = 'RGB'):
    img = Image.fromarray(image, format)
    img.save(filename)

# Reading Image
image = read_image('Images/cat.jpg')
# Removing Noice by applying Gaussian Blur
blurred = GaussianBlur(image, 3)
blurred = np.array(blurred, dtype=np.uint8).tolist()
# Converting RGB to GrayScale Image
gray_image = grayscale(blurred)
gray_image = np.array(gray_image, dtype=np.uint8).tolist()
# Performing Sobel Operator to Detect Edges
sobel = SobelOperator(gray_image)
sobel = np.array(sobel, dtype=np.uint8)

ys,xs = len(image), len(image[0])
#separating gradient and theta
gradient = sobel[:ys, :]
theta = sobel[ys:, :]

gradient = np.array(gradient, dtype=np.uint8)
theta = np.array(theta, dtype=np.uint8)
# Performing Non Maximum Suppression to thin out the edges.
non_max = non_max_suppression(gradient, theta)
non_max = np.array(non_max, dtype=np.uint8)
# Writing Image
write_image('Output/gradient_cat.jpg', gradient, format='L')
write_image('Output/theta_cat.jpg', theta, format='L')
write_image('Output/gradientNtheta_cat.jpg', sobel, format='L')
write_image('Output/nonmax_cat.jpg', non_max, format='L')
# end