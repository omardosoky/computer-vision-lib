# Task 1
### Team members




| Name                | Sec | BN  |
| ------------------- | --- | --- |
| ezzeldeen Esmail    | 1   | 50  |
| Noran ElShahat      | 2   | 40  |
| Moamen Gamal        | 2   | 11  |
| omar sayed          | 2   | 2   |
| Abdelrahman Almahdy | 1   | 45  |

### Questions output and explanation
# Q1: Additive Noise
- This is a sample image i used to work on all noise types
- ![Image Original](./images/1.png)
### Uniform Noise
- Uniform noise works by adding a spechific random value in a certain range on all pixels of the image
- ![Image Original](./images/uniform.png)
### Gaussian Noise
- in gaussian noise , we add values to all pixels in the image according to the gaussian normal distribution formula
- ![Image Original](./images/gaussian.png)
### Salt-Pepper Noise
- in salt-pepper noise, we add either white or dark pixels randomly to the image pixels
- ![Image Original](./images/salt.png)

# Q2: Filtering

### Applying the three filters on Uniform Noise image 

  |        Gaussian filter         |          Mean filter           |         Median filter         |
  | :----------------------------: | :----------------------------: | :---------------------------: |
  | ![](./images/gaws_uniform.png) | ![](./images/mean_uniform.png) | ![](./images/med_uniform.png) |

### Applying the three filters on Gaussian Noise image 

 |       Gaussian filter       |         Mean filter         |       Median filter        |
 | :-------------------------: | :-------------------------: | :------------------------: |
 | ![](./images/gaws_gaws.png) | ![](./images/mean_gaws.png) | ![](./images/med_gaws.png) |


### Applying the three filters on salt Noise image 

 |       Gaussian filter       |         Mean filter         |       Median filter        |
 | :-------------------------: | :-------------------------: | :------------------------: |
 | ![](./images/gaws_salt.png) | ![](./images/mean_salt.png) | ![](./images/med_salt.png) |


<!-- ### Gaussian Noise
- in gaussian noise , we add values to all pixels in the image according to the gaussian normal distribution formula
- ![Image Original](./images/gaussian.png)
### Salt-Pepper Noise
- in salt-pepper noise, we add either white or dark pixels randomly to the image pixels
- ![Image Original](./images/salt.png) -->

# Q3:Edge Detection
### Sobel Edge Detection
- apply sobel's kernel in both x and y directions
- add both images together
### Prewitt's Edge Detection
- apply Prewitt's kernel in both x and y directions
- add both images together
### Robert's Edge Detection
- apply Robert's kernel in both x and y directions
- add both images together

### Canny Edge Detection
- Gauessian blur first
- Gradient and slope calculation using sobel 
- Non maximum suppression
- Double thresholding
- Edge tracking by hysteresis

- ![Image of dorsal](https://i.ibb.co/T0ZT1wF/dobrl.png)

- ![Image of ropert](https://i.ibb.co/51wdbXB/robert.png)
- ![Image of canny](https://i.ibb.co/R3bR5bW/Canny.png)
- ![Image of pweit](https://i.ibb.co/S3z84nc/Capture.png)

# Q4:Histogram and distribution

- First we needed to make array that contains values of pixels density
- After that we made this array using QTcharts in spline mode 
- we also made Bar mode wihich can be given variable inticates how many values of histogram needs to make one bar
- ![Image of HistoDistribution](https://i.ibb.co/1JgsZFL/Capture2.png)
- ![Image of HistoBars](https://i.ibb.co/n7R9pNt/Capture.png)

# Q5:Equalization

- Main idea for rqualization is to make all values near each other and remove any big values considereted 
- this is adchieved in code which  can not be the best in all cases that the apply of scale is applied for
- the start to end meaning if there is a case where histo is distributed at 255 means it will
- not be effected other than that it should make wanted output
- ![Image of HistoDistribution](https://i.ibb.co/JHqnZhC/Captur3e.png)
- ![Image of HistoBars](https://i.ibb.co/drDK37M/Cap4ture.png)

# Q6: Normalization 
- the main purpose of Normalization is to make the pixel intensities cover my whole range which isn't the case for this image.
- ![Image non-Norm](./images/5.png)
- so in order to solve this problem we need to "rescale" the pixel values to cover my range which in my case is form 0-255 grayscale values
- ![Image Norm](./images/normimg.png)

# Q7: Local and Global Threshold 
## Global Threshold
- Thresholding is the simplest method of image segmentation. From a grayscale image, thresholding can be used to create binary images.
- A global thresholding technique makes use of a single threshold value for the whole image.
- Global Threshold has Different Modes as follows:
  ![Image of GT](./images/Thresholding/Glopal_thresholding_Discribtion.jpg)

**Original Image**             |
:-------------------------:|
![Image of GT](./images/Thresholding/Grad.jpg)  |

|                       **Binary Thershold**                        |              **Inverted Binary Thershold**               |
| :---------------------------------------------------------------: | :------------------------------------------------------: |
| ![Image of GT](./images/Thresholding/Binary_Thesholded_Image.jpg) | ![Image of GT](./images/Thresholding/InvertedBinary.jpg) |

**Truncated Thershold**           |
:-------------------------:|
![Image of GT](./images/Thresholding/Truncated.jpg)  |

|               **Zero Thershold**               |              **Inverted Zero Thershold**               |
| :--------------------------------------------: | :----------------------------------------------------: |
| ![Image of GT](./images/Thresholding/Zero.jpg) | ![Image of GT](./images/Thresholding/InvertedZero.jpg) |
  <br />

  ## Local Threshold
- Local adaptive thresholding is used to convert an image consisting of gray scale pixels to just black and white scale pixels. Usually a pixel value of 0 represents white and the value 255.
- Unlike the global thresholding technique, local adaptive thresholding chooses different threshold values for every pixel in the image based on an analysis of its neighboring pixels.
- Local adaptive thresholding has two Modes\
The Mean Mode; Where the threshold value is the mean of neighbourhood area. \
The Gaussian Mode; Where the threshold value is the weighted sum of neighbourhood values where weights are a gaussian window.
- **Original Image**
  <br /> ![Image of GT](./images/Thresholding/Sample.jpg)
- **Mean Mode**
  <br /> ![Image of GT](./images/Thresholding/LocalThesholded(Mean).jpg)
- **Gaussian Mode**
  <br /> ![Image of GT](./images/Thresholding/LocalThesholded(Gaussian).jpg)

# Q8: Histogram RGB 
- As Q4 and Q5 we will make histogram again but this time is RGB so in three layers so we used first split function to split the image to 3 images scaled from 0 to 255 as if it  was gray image then bacme the input for our RGB histogram where used the CCHistogram function again 3 Times and made a refrence to then use in our function by the Mode which was set to 1 in case of RGB and 0 
```c++
{
std::vector <cv::Mat> ImageSplit = Split.Split_Image(ImageColored);
	MisterHisto.RGBHistogram(ImageSplit, 10);
}
```

- one of the things we could have done is to adjust splitting in the function instead of making the input the vector of cv mat of rgb we could split inside the fuction but because we already had split function we used it directly as in vector

- ![RGB](https://i.ibb.co/RPbkhG6/RGB.png)
- ![RGB Bars](https://i.ibb.co/P9dGJ9F/RGBBars.png)
- in case of cumilated it was used in a state where there is no scaling meaning it was before equlaization.
- ![Cumilated](https://i.ibb.co/VY3NpFz/Cumilated.png)
- another point in Q8 was gray scaling which is done by only talking any vector of R , G , B splitted if needed but grayscaling as it is , can be applied by using average or weighted in our case we used weighted method
 - ![Before](https://i.ibb.co/ThJmXHz/Before-Rose.png)
 - ![After Gray](https://i.ibb.co/xDB3Dg3/After-Gray.png)


# Q9: Lowpass & highpass filtering

- Magnitude image after transfering to frequancy domain


- ![magnitude](./images/magnitude_img.png) 

## Applying lowpass filter

|       Low mask        |          Filtered image         |
| :-------------------------: | :-------------------------: |
| ![](./images/low_mask.png) | ![](./images/lowpass.png) | 


## Applying Highpass filter

|       High mask        |          Filtered image         |
| :-------------------------: | :-------------------------: |
| ![](./images/high_mask.png) | ![](./images/highpass.png) | 

# Q10:Hyprid Images
- For hyprid images we need one image to go though a low pass filter and the other to go through high pass filter

|   low pass | high pass | hyprid |
| ![](./images/low.png) | ![](./images/high.png) | ![](./images/hyprid.png)
