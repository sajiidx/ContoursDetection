# pdc-project

## Installing Dependencies
* pip install numpy
* pip install scikit-image






# Object Detection

## Pre-Object Detection Tasks:

### 1. Remove noice by Gaussian Blur

Gaussian Blurring:Gaussian blur is the result of blurring an image by a Gaussian function. It is a widely used effect in graphics software, typically to reduce image noise and reduce detail. It is also used as a preprocessing stage before applying our machine learning or deep learning models. If you take a photo in low light and the resulting image has a lot of noise, Gaussian blur can mute that noise. If you want to lay text over an image, a Gaussian blur can soften the image so the text stands out more clearly.

Gaussian Filtering is widely used in the field of image processing. It is used to reduce the noise of an image. In this article we will generate a 2D Gaussian Kernel. The 2D Gaussian Kernel follows the below given Gaussian Distribution.

<image src='./gaussian.png'> </image>

Where, y is the distance along vertical axis from the origin, x is the distance along horizontal axis from the origin and σ is the standard deviation.

### 2. Covert image to GrayScale

RGB Image- It is three dimension(channel) image. It contains the red color , Green color and Blue color image in separate matrix. Represented from 8bit to 32bit.

GrayScale Image- It is one dimension (channel) image. It is derived from RGB image. It has the intensity value. Using the below equation to compute the gray scale Image.

<image src='./grayscale.png'> </image>

### 3. Apply Sobel Operator


### 4. Canny Edge Detection 