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
  namedWindow("Track Window", 1);
  int window_size = 3;
  createTrackbar("Kernel Dimension", "Track Window", &window_size, 40);
  Mat img;
  cv::Mat imageOne = cv::imread(argv[1],0);
  imshow("Track Window",imageOne);
  waitKey(0);
  if(window_size % 2 == 0){
  	cout << "The window size must be odd, not even. The program will now terminate." << endl;
	exit(-1);
  }
  Mat kernel(window_size,window_size,CV_32F,1);
 
  //Empty check!
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

        double accumulator = 0;
	Mat temp = imageOne.clone();

	Mat frame, frame32;
    	Rect roi;
	//imageOne.rows-window_size/2-1
	//imageOne.cols-window_size/2-1
	//Convolve the kernel across the image by utilizig an roi of the kernel size.
        img = Mat::zeros(imageOne.size(), CV_32F);
    	for(int y=0; y<imageOne.rows-window_size; y++) {
        	for(int x=0; x<imageOne.cols-window_size; x++) {
            		roi = Rect(x,y, window_size, window_size);
            		frame = imageOne(roi);
            		frame.convertTo(frame, CV_32F);
            		frame = frame.mul(kernel);
            		float v = sum(frame)[0];
            		img.at<float>(y,x) = v/(window_size*window_size);
        	}
    	}
    	
	img.convertTo(img, CV_8U);

        /*                   x-1,y-1|x,y-1|x+1,y-1
                             x-1,y  |x,y  |x+1,y
                             x-1,y+1|x,y+1|x+1,y+1
        */
/*        
        //We utilize the box filter with weighted coeffients of one and do standard averaging
        //we will divide each pixel along the way.
        for(int rowNum = 0; rowNum < temp.rows; rowNum++){
                for(int colNum = 0; colNum < temp.cols; colNum++){
			
               	 	if(rowNum - 1 > 0){
				if( colNum - 1 > 0)
                         	accumulator += temp.at<uchar>(rowNum-1,colNum-1);
//				if(colNum - 2 > 0)
//				accumulator += temp.at<uchar>(rowNum-1,colNum-2);
//				if(colNum +2 < imageOne.cols)
//				accumulator += temp.at<uchar>(rowNum-1,colNum+2);
                        	accumulator += temp.at<uchar>(rowNum-1,colNum);
				if( colNum + 1 < imageOne.cols)
				accumulator += temp.at<uchar>(rowNum-1,colNum+1);
			 } 

			 if(rowNum + 1 < imageOne.rows){
				if( colNum - 1 > 0) 
				accumulator += temp.at<uchar>(rowNum+1,colNum-1);
//				if(colNum - 2 > 0)
//				accumulator += temp.at<uchar>(rowNum+1,colNum-2);
//				if(colNum + 2 < imageOne.cols)
//				accumulator += temp.at<uchar>(rowNum+1,colNum+2);
				accumulator += temp.at<uchar>(rowNum+1,colNum);
				if(colNum + 1 < imageOne.cols)
				accumulator += temp.at<uchar>(rowNum+1,colNum+1);
			 }
/*
			 if(rowNum + 2 < imageOne.rows){
				if( colNum - 1 > 0)
                                accumulator += temp.at<uchar>(rowNum+2,colNum-1);
				if(colNum - 2 > 0)
                                accumulator += temp.at<uchar>(rowNum+2,colNum-2);
				if(colNum +2 < imageOne.cols)
                                accumulator += temp.at<uchar>(rowNum+2,colNum+2);
                                accumulator += temp.at<uchar>(rowNum+2,colNum);
                                if(colNum + 1 < imageOne.cols)
                                accumulator += temp.at<uchar>(rowNum+2,colNum+1);

			 }

			if(rowNum -2 > 0){
                                if( colNum - 1 > 0)
                                accumulator += temp.at<uchar>(rowNum-2,colNum-1);
                                if(colNum - 2 > 0)
                                accumulator += temp.at<uchar>(rowNum-2,colNum-2);
                                if(colNum +2 < imageOne.cols)
                                accumulator += temp.at<uchar>(rowNum-2,colNum+2);
                                accumulator += temp.at<uchar>(rowNum-2,colNum);
                                if(colNum + 1 < imageOne.cols)
                                accumulator += temp.at<uchar>(rowNum-2,colNum+1);

                         }
*/
/*			
			 if(colNum -1 > 0)
			 accumulator += temp.at<uchar>(rowNum,colNum-1);
			 if(colNum +1 < imageOne.cols)
                         accumulator += temp.at<uchar>(rowNum,colNum+1);
//			 if(colNum +2 < imageOne.cols)
//			 accumulator += temp.at<uchar>(rowNum,colNum+2);
//			 if(colNum - 2 > 0)
//			 accumulator += temp.at<uchar>(rowNum,colNum-2);
/*                         
                         imageOne.at<uchar>(rowNum,colNum) = floor(accumulator/(SliderValue*SliderValue));
                         accumulator = 0;
                }
        }
*/        
        cv::namedWindow( "Smoothed", cv::WINDOW_AUTOSIZE );
        cv::imshow( "Smoothed", img);
        cv::waitKey(0);            

        return 0;
}

