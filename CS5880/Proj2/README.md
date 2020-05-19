* Project_2
-----------
> In problems 3, 4, 5, if the input is a color image, convert it to grayscale using cvtColor before applying the functions.
> 1. Write a program to compare two grayscale images of the same size. You should compute the average distance between
corresponding pixel intensity levels. For an 8-bit image, the average distance will result in a value between 0 and 255.
Make sure you find the absolute difference between pixels to compute the distance. Also, it will be better to accumulate
the distance as int but report it as a float or double.

> 2. Write a function to convert a color image to a gray scale image. If a color pixel is denoted by p = [R G B]
T, the equivalent grayscale pixel pg is given by pg = [0.30 0.59 0.11]p
Write a program to test your function by converting a color image to grayscale. Compute the distance of your grayscale
converted image from the grayscale conversion by OpenCV (using the function cvtColor) using the program from last
question.

> 3. Write a program that will provide some statistical information on gray scale images. In particular, we want to find out
average gray scale value of pixels as well as standard deviation. In addition, plot a histogram of this image on a 256×256
pixel canvas, with each column of the histogram giving the relative total of the number of pixels at that intensity level.
Draw some conclusions about the image from the histogram and print the same to stdout. The conclusion could be
about the brightness (light/dark) and contrast (low/high) in the image.

> 4. Write a program to subsample a grayscale image by removing alternate rows and columns. Save the subsampled image
and display it to screen as well.

> 5. Write a program to split a grayscale image into bit planes. Save the bit planes and display them on screen as well. Each
bit plane should have two intensities: black (0) and white (255) corresponding to the non-zero pixels in the bit plane.
