/**
 * Author: Jason Klamert
 * Date: 10/09/2016
 * Description: Program to find ROI of image and perform histogram equalization on the ROI. Then display
 * the image with these new changes.
 **/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <cmath>
#define DEBUG false
using namespace cv;
using namespace std;
const int lookup[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384};
//indexes	      0,1,2,3,4 ,5 ,6 ,7  ,8  , 9 , 10 , 11 , 12 , 13 , 14
int getCityBlockDistance(int x1, int x2, int y1, int y2);

int main( int argc, char** argv )
{
  namedWindow("Track Window", 1);
  int window_size = 3;
  int resolution = 1024;
  createTrackbar("Kernel Dimension", "Track Window", &window_size, 40);
  createTrackbar("Kernel Resolution", "Track Window", &resolution, 16384);
  Mat img;
  cv::Mat imageOne = imread(argv[1],0);
  imshow("Track Window",imageOne);
  waitKey(0);
  double radius = window_size/2;

  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

  if(window_size % 2 == 0){
  	cout << "The window size must be odd, not even. The program will now terminate." << endl;
	exit(-1);
  }
  if(resolution > 16384){
  	cout << "Resolution is too large! Please use a smaller resolution!" << endl;
	exit(-1);
  }
  bool contains = false;
  for(int count = 0; count < 15; count++){
	if(resolution == lookup[count])
		contains = true;
  }
  if(contains == false){
	cout << "Resolution is not a power of 2! This must be a power of two. Terminating." << endl;
  	exit(-1);
  }
  else
	cout << "Resolution is a power of 2!" << endl;

  double temp = resolution;
  int power = 0;
  //Get resolution's power of 2.
  while((temp/2) >= 1){
  	temp = temp/2;
	power++;
  }

  float sumOfKernel = 0;
  cout << "Kernel: ";
  Mat kernel(window_size,window_size,CV_32F,1);
  kernel.at<float>(floor(kernel.rows/2),floor(kernel.cols/2)) = resolution;
  for(int rowNum = 0; rowNum < kernel.rows; rowNum++){
	for(int colNum = 0; colNum < kernel.cols; colNum++){
		int distance = getCityBlockDistance(rowNum,floor(kernel.rows/2),colNum,floor(kernel.cols/2));
		int index = power - distance;
		if(index < 0){
			kernel.at<float>(rowNum,colNum) = 0;
		}
		else
		kernel.at<float>(rowNum,colNum) = lookup[index];
		cout << (int) kernel.at<float>(rowNum,colNum) << " ";
		sumOfKernel += kernel.at<float>(rowNum,colNum);
	}
  }
  cout << endl;

	Mat frame, frame32;
    	Rect roi;
	//imageOne.rows-window_size/2-1
	//imageOne.cols-window_size/2-1
	//Convolve the kernel across the image by utilizing an roi of the kernel size.
        img = Mat::zeros(imageOne.size(), CV_32F);
    	for(int y=0; y<imageOne.rows-window_size; y++) {
        	for(int x=0; x<imageOne.cols-window_size; x++) {
            		roi = Rect(x,y, window_size, window_size);
            		frame = imageOne(roi);
            		frame.convertTo(frame, CV_32F);
            		frame = frame.mul(kernel);
            		float v = sum(frame)[0];
            		img.at<float>(y,x) = v/(sumOfKernel);
			if(img.at<float>(y,x) > 255)
				img.at<float>(y,x) = 255;
        	}
    	}
    	
	img.convertTo(img, CV_8U);

        cv::namedWindow( "Smoothed", cv::WINDOW_AUTOSIZE );
        cv::imshow( "Smoothed", img);
        cv::waitKey(0);            

        return 0;
}

/**
 * Author: Jason Klamert
 * Description: City block calculation between two points.
 * Date: 11/13/2016
 **/
int getCityBlockDistance(int x1, int x2, int y1, int y2){

        double diffX = abs(x1 - x2);
        double diffY = abs(y1 - y2);
        
        return (int)  diffX + diffY;
}
