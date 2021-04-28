# Parallel & Distributed Computing (PDC) Semester Project

## Installing Dependencies

* pip install numpy
* pip install scikit-image
* pip install ctypes
* pip install opencv-python
* pip install matplotlib


# Object Detection

## 1. Remove noice by Gaussian Blur

Gaussian Blurring:Gaussian blur is the result of blurring an image by a Gaussian function. It is a widely used effect in graphics software, typically to reduce image noise and reduce detail. It is also used as a preprocessing stage before applying our machine learning or deep learning models. If you take a photo in low light and the resulting image has a lot of noise, Gaussian blur can mute that noise. If you want to lay text over an image, a Gaussian blur can soften the image so the text stands out more clearly.

Gaussian Filtering is widely used in the field of image processing. It is used to reduce the noise of an image. In this article we will generate a 2D Gaussian Kernel. The 2D Gaussian Kernel follows the below given Gaussian Distribution.

<image src='./gaussian.png'> </image>

Where, y is the distance along vertical axis from the origin, x is the distance along horizontal axis from the origin and σ is the standard deviation.

## 2. Covert image to GrayScale


The first step to using any Edge Detection Algorithm is to convert the image to grayscale. While it is possible to use the algorithm in standard RGB scale, it is easier to implement in a grayscale.

RGB Image- It is three dimension(channel) image. It contains the red color , Green color and Blue color image in separate matrix. Represented from 8bit to 32bit.

GrayScale Image- It is one dimension (channel) image. It is derived from RGB image. It has the intensity value. Using the below equation to compute the gray scale Image.

<image src='./grayscale.png'> </image>

## 3. Apply Sobel Operator

Sobel edge detection is one of the foundational building block of Computer Vision. Even when you start learning deep learning if you find the reference of Sobel filter. In this tutorial we will learn How to implement Sobel edge detection using Python from scratch.

### What is an edge?

    An edge is a place of rapid change in the image intensity function.

### How to detect an edge?

    In order to detect edge we need to detect the discontinuities in image
    and we know that we can use derivative to detect discontinuities.

<image src="how-to-detect-edge.webp"> </image>

As you are seeing in the above picture, the edges corresponds to the derivatives. Since images are discrete in nature, we can easily take the derivate of an image using 2D derivative mask.

However derivates are also effected by noise, hence it’s advisable to smooth the image first before taking the derivative. Then we can use the convolution using the mask to detect the edges.

### The Math Behind the Algorithm

When using Sobel Edge Detection, the image is processed in the X and Y directions separately first, and then combined together to form a new image which represents the sum of the X and Y edges of the image. However, these images can be processed separately as well. This will be covered later in this document.

When using a Sobel Edge Detector, it is first best to convert the image from an RGB scale to a Grayscale image. Then from there, we will use what is called kernel convolution. A kernel is a 3 x 3 matrix consisting of differently (or symmetrically) weighted indexes. This will represent the filter that we will be implementing for an edge detection.

When we want to scan across the X direction of an image for example, we will want to use the following X Direction Kernel to scan for large changes in the gradient. Similarly, when we want to scan across the Y direction of an image, we could also use the following Y Direction Kernel to scan for large gradients as well.

<image src="XY_Kernels.png"> </image>

By using Kernel Convolution, we can see in the example image below there is an edge between the column of 100 and 200 values.

<image src="Kernelconvolution.png"> </image>

This Kernel Convolution is an example of an X Direction Kernel usage. If an image were scanning from left to write, we can see that if the filter was set at (2,2) in the image above, it would have a value of 400 and therefore would have a fairly prominent edge at that point. If a user wanted to exaggerate the edge, then the user would need to change the filter values of -2 and 2 to higher magnitude. Perhaps -5 and 5. This would make the gradient of the edge larger and therefore, more noticeable.

Once the image is processed in the X direction, we can then process the image in the Y direction. Magnitudes of both the X and Y kernels will then be added together to produce a final image showing all edges in the image.
    In order to combine both the vertical and horizontal edges (derivatives) we can use the following equation:

<image src="sobel_operator.png"> </image>

    We will implement the same equation and then normalize the output to be between 0 and 255.


### Limitation in Sobel Edge Detection Technique:

    Poor Localization, which means you will see many edges where we actually should have only edge.
    Can miss edges which are neither verticle or horizontal.

Next we will implement Canny edge detector where we will overcome theses issues.

## 4. Canny Edge Detection

