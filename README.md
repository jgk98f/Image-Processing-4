# Image-Processing-4
Image operations involving laplacian enhancement, trackbars, convolution, and noise introduction/reduction.

----------------------------------------------------------------------------
README
----------------------------------------------------------------------------
Author: Jason Klamert
Programs: question[1-6]
Digital Image Processing
----------------------------------------------------------------------------
Summary:
----------------------------------------------------------------------------

The following programs correspond to the questions of project number four and
are named accordingly.

Question 1 takes one image as an arguement grayscale and it 
makes ten noisy images using gaussian noise. They are all displayed and then
the images are summed to produce blur final. The distance is calculated from
this image to the original image.

(I implemented this wrong but I must turn it in on time. I used a weighted kernel.)
Question 2 takes one image as an arguement grayscale and series of parameters
to specify an roi and a zoom factor. Below will be the mention of how to run.
This ROI is zoomed to the specific factor and placed back inside of the original.

Question 3 takes one grayscale image as an input and it will pop up a trackbar
to specify the size of the kernel. This input is taken and is used to make a 
kernel of user x user width and height. Then it used to perform smoothing.

Question 4 takes one image as an arguement and uses two trackbars to specify
kernel size and resolution of the kernel. Then we use the resolution to give
the kernel a weight. This is convolved over the image.

Question 5 is a program that takes one grayscale image as an arguement and
it performs laplacian enhancement to sharpen the image.

Question 6 is a program that takes one image as an argument and a trackbar
appears to specify the pixel fade from the boarder. This program puts a wide
gradient border on an image of user specified pixels.

----------------------------------------------------------------------------
Directions:
----------------------------------------------------------------------------

Makefile:
	make -f MakeFile

clean:
	make -f MakeFile clean

run:
	add_rm_noise imageName numberOfBitsToFlip
	question2 -z zoom -r row -c column -h height -w width -i inputImage -o ouputImage
	sm_filter imageName
	blur imageName
	enh imageName
        question6 imageName


