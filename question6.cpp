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
double getDistance(int, int, int, int);

int main( int argc, char** argv )
{
  	namedWindow("Track Window", 1);
  	int pixelsFromEdge = 25;
  	cv::Mat imageOne = cv::imread(argv[1],0);
  	createTrackbar("Pixels from edge", "Track Window", &pixelsFromEdge, max(imageOne.rows,imageOne.cols));
  	imshow("Track Window",imageOne);
  	waitKey(0);
 
  	//Empty check!
  	if ( imageOne.empty() )
  	{
      		std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      		return ( 1 );
  	}

        double accumulator = 0;
        //Make our white boarder around the image
        for(int rowNum = 0; rowNum < imageOne.rows; rowNum++) {
        	imageOne.at<uchar>(rowNum,0) = 255;
        	imageOne.at<uchar>(rowNum,imageOne.cols-1) = 255;
        }
    	
     	for(int colNum = 0; colNum < imageOne.cols; colNum++) {
    		imageOne.at<uchar>(0,colNum) = 255;
    		imageOne.at<uchar>(imageOne.rows-1,colNum) = 255;
     	}
        //Boarder drawn.
	uchar pixel;
	double distanceCols,distanceRows;
	double n = pixelsFromEdge;
	double temp;

	for(int rowNum = 1; rowNum < imageOne.rows-1; rowNum++){
		for(int colNum = 1; colNum < imageOne.cols-1; colNum++){
			if(((rowNum > pixelsFromEdge) && (rowNum < imageOne.rows - pixelsFromEdge)) && (colNum > pixelsFromEdge) && (colNum < imageOne.cols - pixelsFromEdge))
				continue;
			pixel = imageOne.at<uchar>(rowNum,colNum);
			//Find closest edge and find the distance from current pixel to edge pixel.
			
			if(colNum > floor((imageOne.cols/2)))
			distanceCols = getDistance(imageOne.cols-1,colNum,rowNum,rowNum);
			else
			distanceCols = getDistance(0,colNum,rowNum,rowNum);
			
			if(rowNum > floor((imageOne.rows/2)))
			distanceRows = getDistance(imageOne.rows-1,rowNum,colNum,colNum);
			else	
			distanceRows = getDistance(0,rowNum,colNum,colNum);
			
			temp = abs(n - min(distanceCols,distanceRows));
			temp = temp/n;
			temp *= abs((255-pixel));
			temp = temp + pixel;
			imageOne.at<uchar>(rowNum,colNum) = (uchar) temp;
		}
	}

        cv::namedWindow( "Pastel", cv::WINDOW_AUTOSIZE );
        cv::imshow( "Pastel", imageOne);
        cv::waitKey(0);            

        return 0;
}

double getDistance(int x1, int x2, int y1, int y2){

        double sumX = x1 - x2;
        double sumY = y1 - y2;
        double squareX = sumX * sumX;
        double squareY = sumY * sumY;
        double distance = sqrt(squareX + squareY);
	
        return distance;
}
