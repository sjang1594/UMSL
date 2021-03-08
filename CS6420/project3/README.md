# Project 3 : Denoising the periodic noise in frequency domain.
---

## Project Description

### Usage : 

``cd build && cmake ..``, then `make`

---
**Command Line Argument**
```./freq_filter [-h] input_image [output_image]```

**Here is the information for each arguments :**
- ./freq_filter     : Name of executable (register)
- input_image       : Perform Manual Registration
- output_image      : ECC's convergence epsilon [default: 0.0001]

### I/O Image
<p align="center">
  <img src="./img/input.jpg" width="320" height="200" >
  <img src="./img/Filtered_img.jpg" width="320" height="200" >
</p>


### 

## Reference :
* [Descrete Fourier Transform](https://docs.opencv.org/3.4/de/dbc/tutorial_py_fourier_transform.html)
* [Contours](https://docs.opencv.org/3.4/d4/d73/tutorial_py_contours_begin.html)
