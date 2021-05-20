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

One last important thing to mention, is that the algorithm is based on grayscale pictures. Therefore, the pre-requisite is to convert the image to grayscale before following the above-mentioned steps.

The Canny edge detection algorithm is composed of 5 steps:

### 1. Noise reduction;

Since the mathematics involved behind the scene are mainly based on derivatives (cf. Step 2: Gradient calculation), edge detection results are highly sensitive to image noise.

One way to get rid of the noise on the image, is by applying Gaussian blur to smooth it. To do so, image convolution technique is applied with a Gaussian Kernel (3x3, 5x5, 7x7 etc…). The kernel size depends on the expected blurring effect. Basically, the smallest the kernel, the less visible is the blur. In our example, we will use a 5 by 5 Gaussian kernel.

The equation for a Gaussian filter kernel of size (2k+1)×(2k+1) is given by:

<image src="noice.png"> </image>

### 2. Gradient calculation;

The Gradient calculation step detects the edge intensity and direction by calculating the gradient of the image using edge detection operators.

Edges correspond to a change of pixels’ intensity. To detect it, the easiest way is to apply filters that highlight this intensity change in both directions: horizontal (x) and vertical (y)

When the image is smoothed, the derivatives Ix and Iy w.r.t. x and y are calculated. It can be implemented by convolving I with Sobel kernels Kx and Ky, respectively:

<image src="sobel_filter.png"> </image>

Sobel filters for both direction (horizontal and vertical)

Then, the magnitude G and the slope θ of the gradient are calculated as follow

<image src="Gradient-intensity .png"> </image>

Gradient intensity 

### 3. Non-maximum suppression;

Ideally, the final image should have thin edges. Thus, we must perform non-maximum suppression to thin out the edges.

The principle is simple: the algorithm goes through all the points on the gradient intensity matrix and finds the pixels with the maximum value in the edge directions.

Let’s take an easy example:

<image src="a1.png"> </image>

Ideally, the final image should have thin edges. Thus, we must perform non-maximum suppression to thin out the edges.

The principle is simple: the algorithm goes through all the points on the gradient intensity matrix and finds the pixels with the maximum value in the edge directions.

Let’s take an easy example:

<image src="a2.png"> </image>

The edge direction is the orange dotted line (horizontal from left to right). The purpose of the algorithm is to check if the pixels on the same direction are more or less intense than the ones being processed. In the example above, the pixel (i, j) is being processed, and the pixels on the same direction are highlighted in blue (i, j-1) and (i, j+1). If one those two pixels are more intense than the one being processed, then only the more intense one is kept. Pixel (i, j-1) seems to be more intense, because it is white (value of 255). Hence, the intensity value of the current pixel (i, j) is set to 0. If there are no pixels in the edge direction having more intense values, then the value of the current pixel is kept.

Let’s now focus on another example:

<image src="a3.png"> </image>

In this case the direction is the orange dotted diagonal line. Therefore, the most intense pixel in this direction is the pixel (i-1, j+1).

Let’s sum this up. Each pixel has 2 main criteria (edge direction in radians, and pixel intensity (between 0–255)). Based on these inputs the non-max-suppression steps are:

* Create a matrix initialized to 0 of the same size of the original gradient intensity matrix;
* Identify the edge direction based on the angle value from the angle matrix;
* Check if the pixel in the same direction has a higher intensity than the pixel that is currently processed;
* Return the image processed with the non-max suppression algorithm.

### 4. Double threshold;

The double threshold step aims at identifying 3 kinds of pixels: strong, weak, and non-relevant:

* Strong pixels are pixels that have an intensity so high that we are sure they contribute to the final edge.
* Weak pixels are pixels that have an intensity value that is not enough to be considered as strong ones, but yet not small enough to be considered as non-relevant for the edge detection.
* Other pixels are considered as non-relevant for the edge.

Now you can see what the double thresholds holds for:

* High threshold is used to identify the strong pixels (intensity higher than the high threshold)
* Low threshold is used to identify the non-relevant pixels (intensity lower than the low threshold)
* All pixels having intensity between both thresholds are flagged as weak and the Hysteresis mechanism (next step) will help us identify the ones that could be considered as strong and the ones that are considered as non-relevant.

### 5. Edge Tracking by Hysteresis.
