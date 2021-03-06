#include "statisticalDescriptor.h"

void  statisticalDescriptor::StatisticalDescriptor(string filename)
{
	
	Mat image,gray;
    VideoCapture cap(filename);
    int sumx=0,sumy=0,pixelNum=0;
    double centroidX=0,centroidY=0; 
    Point newPoint;
    
	cap>>image;
	
	cvtColor(image, gray, CV_BGR2GRAY);
    Canny(gray, gray, 100, 200, 3);
	
	//Centroid Bulma
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
	      	if(image.at<cv::Vec3b>(i,j) == cv::Vec3b(255,255,255)
	      		||image.at<cv::Vec3b>(i,j) != cv::Vec3b(0,0,0))
	      	{
	      		sumx+=i;
	      		sumy+=j;
	      		pixelNum++;
	      	}
		}
	}
	
	centroidX=static_cast<double>(sumx)/pixelNum;
	centroidY=static_cast<double>(sumy)/pixelNum;	
	
	newPoint=MaxDistanceFromCentroidToContour(centroidX,centroidY,gray);

	
	int partition=11;
	double radius=0;
	int sum[10]={0};
	int j=0;
	double maxDistance;
	
	maxDistance=EucliedianDistance(newPoint.x,newPoint.y,centroidX,centroidY);
	
	radius=static_cast<double>(maxDistance)/partition;
	
		for(double i=radius;i<maxDistance;i=i+radius)
		{	
			for(double k=i-radius;k<i;k++)
			{	
				for(double l=i-radius;l<i;l++)
				{
					
					if(centroidX-k<0||centroidY-k<0||centroidX-l<0||centroidY-l<0)break;
					if(centroidX+k>image.rows||centroidY+l>image.cols) break;
				
					if(image.at<cv::Vec3b>(centroidX-k,centroidY-l) == cv::Vec3b(255,255,255)
	      			||image.at<cv::Vec3b>(centroidX-k,centroidY-l) != cv::Vec3b(0,0,0))
	      			{
	      			rates[j]++;
	      			}
	      			if(image.at<cv::Vec3b>(centroidX+k,centroidY-l) == cv::Vec3b(255,255,255)
	      			||image.at<cv::Vec3b>(centroidX+k,centroidY-l) != cv::Vec3b(0,0,0))
	      			{
	      			rates[j]++;
	      			}
			  		if(image.at<cv::Vec3b>(centroidX-k,centroidY+l) == cv::Vec3b(255,255,255)
			  		||image.at<cv::Vec3b>(centroidX-k,centroidY+l) != cv::Vec3b(0,0,0))
			  		{
			  			rates[j]++;
			  		}
			  		if(image.at<cv::Vec3b>(centroidX+k,centroidY+l) == cv::Vec3b(255,255,255)
			  		||image.at<cv::Vec3b>(centroidX+k,centroidY+l) != cv::Vec3b(0,0,0))
			  		{
			  			rates[j]++;
			  		}	
			  	}
			}
			j++;		
		
	}	
	

}
double statisticalDescriptor::EucliedianDistance(int value1X,int value1Y,int value2X,int value2Y)
{
	double val;

		val=sqrt((value2X-value1X)*(value2X-value1X)+(value2Y-value1Y)*(value2Y-value1Y));

	return val;
}
Point statisticalDescriptor::MaxDistanceFromCentroidToContour(double centroidX,double centroidY,Mat gray)
{
	int minvalIndexX=0,maxvalIndexX=0,minvalIndexY=0,maxvalIndexY=0;
	double minvalX=10000,minXdependY=0;	
	double maxvalX=-10000,maxXdependY=0;
	double minvalY=10000,minYdependX=0;	
	double maxvalY=-10000,maxYdependX=0;
	int valueResult[6];	
 	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
  	Point values;	  

	findContours(gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	
	for(int j=0;j<contours.size();j++)	
	{
	 	for(int i=0;i<contours[j].size();i++)
	 	{		
			if(minvalX>contours[j][i].x)
			{
			minvalX=contours[j][i].x;	
			minvalIndexX=i;
			}
		}
		minXdependY=contours[j][minvalIndexX].y;
	
		for(int i=0;i<contours[j].size();i++)		
		{	
			if(maxvalX<contours[j][i].x)
			{
			maxvalX=contours[j][i].x;	
			maxvalIndexX=i;
			}
		}
		maxXdependY=contours[j][maxvalIndexX].y;
	
	
		for(int i=0;i<contours[j].size();i++)		
		{	
			if(minvalY>contours[j][i].y)
			{
				minvalY=contours[j][i].y;	
				minvalIndexY=i;
			}	
		}
		minYdependX=contours[j][minvalIndexY].x;


		for(int i=0;i<contours[j].size();i++)		
		{
			if(maxvalY<contours[j][i].y)
			{
				maxvalY=contours[j][i].y;	
				maxvalIndexY=i;
			}
		}
		maxYdependX=contours[j][maxvalIndexY].x;
	}
	
	int max=0,j=0;
	int value[4];
	
	value[0]=EucliedianDistance(minvalX,minXdependY,centroidX,centroidY);
	value[1]=EucliedianDistance(maxvalX,maxXdependY,centroidX,centroidY);
	value[2]=EucliedianDistance(minvalY,minYdependX,centroidX,centroidY);
	value[3]=EucliedianDistance(minvalY,minYdependX,centroidX,centroidY);
		
	if(value[0]>max)			
	{
		j++;			
	}	
		
	if(value[1]>max)			
	{
		j++;			
	}	
		
	if(value[2]>max)			
	{
		j++;			
	}	
		
	if(value[3]>max)			
	{
		j++;			
	}	


	if(j==1) return Point(minvalX,minXdependY);
	if(j==2) return Point(maxvalX,maxXdependY);
	if(j==3) return Point(minvalY,minYdependX);
	if(j==4) return Point(minvalY,minYdependX);
	
}
