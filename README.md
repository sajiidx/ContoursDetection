# pdc-project

## Installing Dependencies
* pip install numpy
* pip install scikit-image

RGB Image- It is three dimension(channel) image. It contains the red color , Green color and Blue color image in separate matrix. Represented from 8bit to 32bit.

GrayScale Image- It is one dimension (channel) image. It is derived from RGB image. It has the intensity value. Using the below equation to compute the gray scale Image.

<image src='./grayscale.png'> </image>


# Object Detection

## Pre-Object Detection Tasks:

1. Remove noice by Gaussian Blur
2. Covert image to GrayScale
3. Apply Sobel Operator
4. Canny Edge Detection 