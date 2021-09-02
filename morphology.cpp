#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat srcGray;
RNG rng(12345);
Mat ShapeErosion(Mat image,int whitePixelNum,int erosionNum);
Mat ShapeDilation(Mat image,int whitePixelNum,int erosionNum);

int main(int argc, char **argv)
{

	int val1=0;
	VideoCapture cap("/home/alico/Masaüstü/trainSet/carriage-02.gif");
	
	cap>>src;


    // Convert image to gray and blur it
    cvtColor(src, srcGray, CV_BGR2GRAY);
    blur(srcGray, srcGray, Size(3, 3));
		
    Mat srcThresh,Image,newImage;
    double otsu;
    
	imshow("first",src);

	
		for(int i=0;i<src.rows;i++)
		{
			for(int j=0;j<src.cols;j++)
			{
					if(src.at<cv::Vec3b>(i,j)==cv::Vec3b(255,255,255))val1++;	
			}
		}
				
		
			
	     Image=ShapeErosion(src,val1,25);
		 newImage=ShapeDilation(src,val1,25);
	

    otsu = threshold(srcGray, srcThresh, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    Mat cannyOut;
    Canny(srcGray, cannyOut, otsu, otsu * 1 / 2, 3, 1);

    // Find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(cannyOut, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    // Draw contours
    Mat drawing = Mat::zeros(cannyOut.size(), CV_8UC3);
    string sObjectNumber;          // string which will contain the result
    ostringstream sContourNumber;   // stream used for the conversion

    for (int i = 0; i< contours.size(); i++)
    {  
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
//        imshow("Contours", drawing);
//        waitKey();
    }


	 imshow("Contours",newImage);
   

    waitKey(0);
    return(0);
}

Mat ShapeErosion(Mat image,int val1,int erosionNum)
{
	int valW=0,valB=0;
	Mat newImage=image;
	int val2=0;

		for(int i=0;i<image.rows;i++)
		{
			for(int j=0;j<image.cols;j++)
			{
				//structuring element                                                
				for(int a=1;a<((erosionNum-1)/2);a++)                                     
				{
				    
					if(i-a<0||j-a<0||i+a>image.rows||j+a>image.cols)valB++;
					else
					{
					
						if(a==1)
				    	{if(image.at<cv::Vec3b>(i,j)!=cv::Vec3b(255,255,255))valB++;else valW++;}

						if(image.at<cv::Vec3b>(i-a,j-a)!=cv::Vec3b(255,255,255))valB++;else valW++;			
 						if(image.at<cv::Vec3b>(i-a,j+a)!=cv::Vec3b(255,255,255))valB++;else valW++;
 						if(image.at<cv::Vec3b>(i+a,j-a)!=cv::Vec3b(255,255,255))valB++;else valW++;
 						if(image.at<cv::Vec3b>(i+a,j-a)!=cv::Vec3b(255,255,255))valB++;else valW++;	
					}
				}
				if(valB>valW)
				{				
					newImage.at<cv::Vec3b>(i,j)=cv::Vec3b(0,0,0);
				}

				valB=0;
				valW=0;
			}
		}

		
		for(int i=0;i<image.rows;i++)
		{
			for(int j=0;j<image.cols;j++)
			{
								
						if(newImage.at<cv::Vec3b>(i,j)==cv::Vec3b(255,255,255))val2++;		
			}
		}
		cout<<val1-val2<<" ";	
	
				
	return newImage;
}
Mat ShapeDilation(Mat image,int val1,int erosionNum)
{
	int valW=0,valB=0;
	Mat newImage=image;
	



		for(int i=0;i<image.rows;i++)
		{
			for(int j=0;j<image.cols;j++)
			{
				// Structuring element
				for(int a=1;a<((erosionNum-1)/2);a++)
				{
				    if(i-a<0||j-a<0||i+a>image.rows||j+a>image.cols)valB++;						
					else
					{				
						if(a==1)
				    	{if(image.at<cv::Vec3b>(i,j)==cv::Vec3b(255,255,255))valW++;else valB++;}
						
						if(image.at<cv::Vec3b>(i-a,j-a)==cv::Vec3b(255,255,255))valW++;else valB++;			
 						if(image.at<cv::Vec3b>(i-a,j+a)==cv::Vec3b(255,255,255))valW++;else valB++;
 						if(image.at<cv::Vec3b>(i+a,j-a)==cv::Vec3b(255,255,255))valW++;else valB++;
 						if(image.at<cv::Vec3b>(i+a,j-a)==cv::Vec3b(255,255,255))valW++;else valB++;	
						
					}
				}
				if(valW>valB)
				{				
					newImage.at<cv::Vec3b>(i,j)=cv::Vec3b(255,255,255);
				}

				valB=0;
				valW=0;
			}
		}	

		int val2=0;
		for(int i=0;i<image.rows;i++)
		{
			for(int j=0;j<image.cols;j++)
			{
								
						if(newImage.at<cv::Vec3b>(i,j)==cv::Vec3b(255,255,255))val2++;		
			}
		}
		cout<<val1-val2<<" ";	
					
	return newImage;
}
