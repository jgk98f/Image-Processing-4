/*
 * question1.cpp
 * Description: Program to introduce gaussian noise. Then we add up the images and display them for the user as well as the intermediate  * images.
 * Created on: 11/11/2016
 * Author: Jason Klamert
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#define DEBUG false
using namespace std;
using namespace cv;
float getDistance(Mat,Mat);
void flipNBits(int, Mat, Mat);
int getRandom();
void display(Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat);
void sumImages(Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat,Mat);
const int powers[] = {0,1,2,4,8,16,32,64,128};

int main( int argc, char** argv )
{
  srand(time(NULL));
  
  //Usage check.
  if ( argc != 3 )
    {
        std::cerr << "usage: " << "Program takes an image and a number of bits to be flipped as arguments!" << std::endl;
	std::cerr << "add_rm_noise image numberOfBitsFlipped" << endl;
        return ( 1 );
    }
  
  cv::Mat original = cv::imread(argv[1],0);
  int numberOfBitsToFlip = atoi(argv[2]);

  //Check if imageOne empty.
  if ( original.empty() )
  {
      std::cerr << "Image is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

  cout << "Number of Bits to Flip: " << numberOfBitsToFlip << endl;  

  Mat temp = original.clone();
  Mat blur1 = original.clone();
  Mat blur2 = original.clone();
  Mat blur3 = original.clone();
  Mat blur4 = original.clone();
  Mat blur5 = original.clone();
  Mat blur6 = original.clone();
  Mat blur7 = original.clone();
  Mat blur8 = original.clone();
  Mat blur9 = original.clone();
  Mat blur10 = original.clone();
  Mat blurFinal = original.clone();
  blurFinal.mul(0);  

  flipNBits(numberOfBitsToFlip,temp,blur1);
  flipNBits(numberOfBitsToFlip,temp,blur2);
  flipNBits(numberOfBitsToFlip,temp,blur3);
  flipNBits(numberOfBitsToFlip,temp,blur4);
  flipNBits(numberOfBitsToFlip,temp,blur5);
  flipNBits(numberOfBitsToFlip,temp,blur6);
  flipNBits(numberOfBitsToFlip,temp,blur7);
  flipNBits(numberOfBitsToFlip,temp,blur8);
  flipNBits(numberOfBitsToFlip,temp,blur9);
  flipNBits(numberOfBitsToFlip,temp,blur10);
  
  sumImages(blur1,blur2,blur3,blur4,blur5,blur6,blur7,blur8,blur9,blur10,blurFinal);

  std::cout << "Average difference across the blurred additions and the original image is: " << getDistance(original,blurFinal) << std::endl;

  display(original,blur1,blur2,blur3,blur4,blur5,blur6,blur7,blur8,blur9,blur10,blurFinal); 

  return 0;
}

/**
 * Author: Jason Klamert
 * Date: 11/11/2016
 * Description: Function to sum all of the blurred images.
 **/
void sumImages(Mat blur1,Mat blur2,Mat blur3,Mat blur4,Mat blur5,Mat blur6,Mat blur7,Mat blur8,Mat blur9,Mat blur10,Mat blurFinal){

	for(int rowNum = 0; rowNum < blurFinal.rows; rowNum++){
                for(int colNum = 0; colNum < blurFinal.cols; colNum++){
                	blurFinal.at<uchar>(rowNum,colNum) = blur1.at<uchar>(rowNum,colNum) + 
			blur2.at<uchar>(rowNum,colNum) + blur3.at<uchar>(rowNum,colNum) + 
			blur4.at<uchar>(rowNum,colNum) + blur5.at<uchar>(rowNum,colNum) + 
			blur6.at<uchar>(rowNum,colNum) + blur7.at<uchar>(rowNum,colNum) + 
			blur8.at<uchar>(rowNum,colNum) + blur9.at<uchar>(rowNum,colNum) + 
			blur10.at<uchar>(rowNum,colNum);
			
			if(blurFinal.at<uchar>(rowNum,colNum) > 255)
				blurFinal.at<uchar>(rowNum,colNum) = 255;
                }
        }

}

/**
 * Author: Jason Klamert
 * Date: 11/11/2016
 * Descirption: Display all images.
 **/
void display(Mat original,Mat blur1,Mat blur2,Mat blur3,Mat blur4,Mat blur5,Mat blur6,Mat blur7,Mat blur8,Mat blur9,Mat blur10,Mat blurFinal){
	namedWindow( "original", WINDOW_AUTOSIZE );
    	imshow( "original", original );
    	waitKey(0);

	namedWindow( "blur1", WINDOW_AUTOSIZE );
    	imshow( "blur1", blur1 );                   
	waitKey(0);  
	imwrite( "./blur1.jpg", blur1 );

	namedWindow( "blur2", WINDOW_AUTOSIZE );
    	imshow( "blur2", blur2 );                  
	waitKey(0);  
	imwrite( "./blur2.jpg", blur2 );

	namedWindow( "blur3", WINDOW_AUTOSIZE );
    	imshow( "blur3", blur3 );                  
	waitKey(0);  
        imwrite( "./blur3.jpg", blur3 );

	namedWindow( "blur4", WINDOW_AUTOSIZE );
    	imshow( "blur4", blur4 );               
	waitKey(0);  
        imwrite( "./blur4.jpg", blur4 );

	namedWindow( "blur5", WINDOW_AUTOSIZE );
    	imshow( "blur5", blur5 );               
	waitKey(0);
        imwrite( "./blur5.jpg", blur5 );

	namedWindow( "blur6", WINDOW_AUTOSIZE );
        imshow( "blur6", blur6 );
        waitKey(0);
        imwrite( "./blur6.jpg", blur6 );

	namedWindow( "blur7", WINDOW_AUTOSIZE );
        imshow( "blur7", blur7 );
        waitKey(0);
        imwrite( "./blur7.jpg", blur7 );

	namedWindow( "blur8", WINDOW_AUTOSIZE );
        imshow( "blur8", blur8 );
        waitKey(0);
        imwrite( "./blur8.jpg", blur8 );

	namedWindow( "blur9", WINDOW_AUTOSIZE );
        imshow( "blur9", blur9 );
        waitKey(0);
        imwrite( "./blur9.jpg", blur9 );

	namedWindow( "blur10", WINDOW_AUTOSIZE );
        imshow( "blur10", blur10 );
        waitKey(0);
        imwrite( "./blur10.jpg", blur10 );

	namedWindow( "blurFinal", WINDOW_AUTOSIZE );
        imshow( "blurFinal", blurFinal );
        waitKey(0);
    
}

/**
 * Author: Jason Klamert
 * Date: 11/11/2016
 * Description: Function to flip N bits in a pixel across a given image.
 **/
void flipNBits(int n, Mat image, Mat blur){
	
	for(int rowNum = 0; rowNum < image.rows; rowNum++){
		for(int colNum = 0; colNum < image.cols; colNum++){
			for(int count = 0; count < n; count++){
				blur.at<uchar>(rowNum,colNum) = image.at<uchar>(rowNum,colNum) ^ powers[getRandom()];
			}
		}
	} 
}

/**
 * Author: Jason Klamert
 * Date: 11/11/2016
 * Description: Return random from 0-7
 **/
int getRandom(){
	return rand() % 8;
}

/**
 * Author: Jason Klamert
 * Date: 11/11/2016
 * Description: Find and return average distance across the image.
 **/
float getDistance(Mat imageOne, Mat imageTwo){

  	int accumulator = 0;
  	float result = 0;
  	int temp = 0;
  	int temp2 = 0;

  	//Iterate through imageOne and two and calculate absolute distance. Accumulate this distance for later.
	for(int rowNum = 0; rowNum < imageOne.rows; rowNum++ ){
  		for(int colNum = 0;colNum < imageOne.cols; colNum++){
			temp = (int) imageOne.at<uchar>(rowNum,colNum);                                                                                          
			temp2 = (int) imageTwo.at<uchar>(rowNum, colNum);
			accumulator += abs(temp - temp2);
  		}
	}

	//Use our accumulated absolute difference to find the average distance between the two images.
	float totalPixels = (int) imageOne.rows * imageOne.cols;
	result = (accumulator/totalPixels);

	return result;
}
