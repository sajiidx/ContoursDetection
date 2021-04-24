from skimage.io import imread
import numpy as np
im = imread("Images/cat.jpg")

indices = np.dstack(np.indices(im.shape[:2]))
data = np.concatenate((im, indices), axis=-1)

print(data)