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

int main( int argc, char** argv )
{
  double minValue;
  double maxValue;
  Point minLocation;
  Point maxLocation;

  int window_size = 3;
  Mat img;
  cv::Mat imageOne = cv::imread(argv[1],0);
 
  Mat kernel = (Mat_<float>(3,3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);  

/*
	0,  1, 0,
	1, -4, 1,
	0,  1, 0
*/
 
  //Empty check!
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

	     Mat frame, frame32;
	     Rect roi;
         
         //Convolve the kernel across the image by utilizig an roi of the kernel size.
        img = Mat::zeros(imageOne.size(), CV_32F);
    	for(int y=0; y<imageOne.rows-window_size/2-1; y++) {
        	for(int x=0; x<imageOne.cols-window_size/2-1; x++) {
            		roi = Rect(x,y, window_size, window_size);
            		frame = imageOne(roi);
            		frame.convertTo(frame, CV_32F);
            		frame = frame.mul(kernel);
            		float v = sum(frame)[0];
            		img.at<float>(y,x) = v;
        	}
    	}
    	
	img.convertTo(img, CV_8U);     

	minMaxLoc( img, &minValue, &maxValue, &minLocation, &maxLocation );
	int temp = (int)  minValue;
	unsigned char min = (unsigned char) temp;
	int temp2 = (int) maxValue;
	unsigned char max = (unsigned char) temp2;

	for(int rowNum = 0; rowNum < img.rows; rowNum++){
		for(int colNum = 0; colNum < img.cols; colNum++){
			img.at<uchar>(rowNum,colNum) = img.at<uchar>(rowNum,colNum) +  min;
			img.at<uchar>(rowNum,colNum) = (255 * (img.at<uchar>(rowNum,colNum) / max));
			imageOne.at<uchar>(rowNum,colNum) = imageOne.at<uchar>(rowNum,colNum) -  img.at<uchar>(rowNum,colNum);
			if(imageOne.at<uchar>(rowNum,colNum) < 0)
			imageOne.at<uchar>(rowNum,colNum) = 0;
			
		}
	}

        cv::namedWindow( "Enhanced", cv::WINDOW_AUTOSIZE );
        cv::imshow( "Enhanced", imageOne);
        cv::waitKey(0);            

        return 0;
}

