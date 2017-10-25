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
	string outputFile = ""; 
    	int zoom, centerX, centerY, width, height;
 	char c;
	Mat imageOne;
	
	while ((c = getopt (argc, argv, ":z:r:h:c:w:i:o:")) != -1){
		switch (c)
      		{
      		case 'z':
		zoom = atoi(optarg);
                if(zoom <= 0){
                        cout << "Negative or zero zoom passed. Terminating." << endl ;
                        exit( -1 );
                }
	        break;
		case 'r':
                centerX = atoi(optarg);
                if(centerX < 0){
                        cout << "Negative row passed. Terminating." << endl ;
                        exit( -1 );
                }
		break;
		case 'h':
		height = atoi(optarg);
		if(height < 0){
                        cout << "Negative height passed. Terminating." << endl ;
                        exit( -1 );
                }
		break;
                case 'c':
                centerY = atoi(optarg);
                if(centerY < 0){
                        cout << "Negative column passed. Terminating." << endl ;
                        exit( -1 );
                }
   	        break;
                case 'w':
		width = atoi(optarg);
		if(width < 0){
                        cout << "Negative width passed. Terminating." << endl ;
                        exit( -1 );
                }
		break;
		case 'i':
		imageOne = imread(optarg,0);
		break;
		case 'o':
		outputFile = optarg;
		break;	
		default:
                std::cerr << "usage: " << "Program " << argv[0] << " takes an image as an argument!\n" 
	            << " You may choose to specify a region of interest by calling the program like this: "
                << "question2 -z zoom -r row# -c col# -w width -h height -i input.jpg -o outputFileName" << std::endl;
				return -1;
      		}
	}

  if(width > imageOne.cols){
  	cout << "width is too large. Terminating." << endl;
  	exit(-1);
  }
  if(height > imageOne.rows){
  	cout << "height is too large. Terminating." << endl;
  	exit(-1);
  }
  if(zoom > max(imageOne.cols, imageOne.rows)){
  	cout << "Zoom is greater than the max(columns,rows)! We will terminate. Please use a smaller value of zoom." << endl;
  	exit(-1);
  }

  //Empty check!
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

   if(zoom != 1){
	int topRightX = centerX + ceil(width/2);
	int topRightY = centerY + ceil(height/2);
	int bottomLeftX = centerX - ceil(height/2);
	int bottomLeftY = centerX - ceil(height/2);
	cout << "Center X: " << centerX << " Center Y: " << centerY << endl;
	cout << "topRightX: " << topRightX << " topRightY: " << topRightY << endl;
	cout << "bottomLeftX: " << bottomLeftX << " bottomLeftY: " << bottomLeftY << endl;
        Rect roi(Point(bottomLeftX, bottomLeftY), Point(topRightX,topRightY));
	Mat image_roi = imageOne(roi);
	Mat temp(image_roi.rows*zoom,image_roi.cols*zoom,CV_8UC1);

        for(int rowNum = 0; rowNum < image_roi.rows; rowNum++){
		for(int colNum = 0; colNum < image_roi.cols; colNum++){
			temp.at<uchar>(rowNum * zoom, colNum * zoom) = image_roi.at<uchar>(rowNum,colNum);
		}
	}

        double accumulator = 0;
	cout << "image channels: " << imageOne.channels() << endl;

/*
                      x-2,y-2|x-1,y-2|x,y-2|x+1,y-2|x+2,y-2
                      x-2,y-1|x-1,y-1|x,y-1|x+1,y-1|x+2,y-1
                       x-2,y |x-1,y  |x,y  |x+1,y  |x+2,y
                      x-2,y+1|x-1,y+1|x,y+1|x+1,y+1|x+2,y+1
                      x-2,y+2|x-1,y+2|x,y+2|x+1,y+2|x+2,y+2
*/
        
        //We shall go over the new pixels and give them values by using 3x3 nearest neighbor interpolation.
        //I experimented with 5x5 nearest neighbor to try and achieve better quality at high zoom but it didn't work out.
        //3x3 has produced far better results.
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
			
			 if(colNum -1 > 0)
			 accumulator += temp.at<uchar>(rowNum,colNum-1);
			 if(colNum +1 < imageOne.cols)
                         accumulator += temp.at<uchar>(rowNum,colNum+1);
//			 if(colNum +2 < imageOne.cols)
//			 accumulator += temp.at<uchar>(rowNum,colNum+2);
//			 if(colNum - 2 > 0)
//			 accumulator += temp.at<uchar>(rowNum,colNum-2);
                         
                         temp.at<uchar>(rowNum,colNum) = floor(accumulator/8);
                         accumulator = 0;
                }
        }
        
        Mat zoomed = temp(roi);
        
        for(int rowNum = 0; rowNum < zoomed.rows; rowNum++){
                for(int colNum = 0; colNum < zoomed.cols; colNum++){
                        image_roi.at<uchar>(rowNum,colNum) = zoomed.at<uchar>(rowNum,colNum);
                }
        }
    }
        cv::namedWindow( "Zoomed", cv::WINDOW_AUTOSIZE );
        cv::imshow( "Zoomed", imageOne );
        cv::waitKey(0);            

	imwrite(outputFile,imageOne);

        return 0;
}

