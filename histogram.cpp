#include "histogram.h"

Histogram::Histogram()
{
	blackRate=1.0;
	whiteRate=1.0;
}

void Histogram::histogramCoding(string filename)
{
	Mat src,dst;
	double valueBlack=0, valueWhite=0;
	    
	 VideoCapture cap(filename);

  /// Load image
  cap>>src; 
  
  if( !src.data )
    { return ; }

	unsigned char *input = (unsigned char*)(src.data);
	
	int i,j;
	
	
	for(int i = 0;i < src.rows ;i++){
        for(int j = 0;j < src.cols ;j++){
    
 			if(src.at<cv::Vec3b>(i,j) == cv::Vec3b(255,255,255))       	
 			valueWhite++;
 			if(src.at<cv::Vec3b>(i,j) == cv::Vec3b(0,0,0))       	
 			valueBlack++;
        }
    }
	
	
	blackRate=(valueBlack/((src.rows)*(src.cols)));
	whiteRate=(valueWhite/((src.rows)*(src.cols)));
}
