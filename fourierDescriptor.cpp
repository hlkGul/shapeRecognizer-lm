#include "fourierDescriptor.h"

Fourier::Fourier()
{
}

double Fourier::getFourierCoefficient(int i)
{
		return FourierCoefficients[i];
}

void Fourier::FourierDescriptor(string filename)
{
	Mat image;
    VideoCapture cap(filename);
    int sumx=0,sumy=0,pixelNum=0;
    double centroidX=0,centroidY=0; 
    
	cap>>image;
	
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
	//Centroid Sonu
	double maxDistance=0;
	maxDistance=findMaximumDistanceToCentroid(centroidX,centroidY,image);
	
	int maxFrequenceI=5,maxFrequenceJ=5;	
	double realPartition[5][5]={0};
	double imaginaryPartition[5][5]={0};	
	
	// DFT
	// Fourier Hesabı
	for(int i=0;i<maxFrequenceI;i++)
	{
		for(int j=0;j<maxFrequenceJ;j++)
		{
			for(int x=0;x<image.rows;x++)
			{
				for(int y=0;y<image.cols;y++)
				{
					//amplitude
					double radius= sqrt(pow((x-maxDistance),2)+pow((y-maxDistance),2));
					//Phase angle 
					double theta=atan2(y-maxDistance,x-maxDistance);
					if(theta<0.0)
					{
						theta+= 2*PI;
					}
					int pixelValue=0;
						
						if(image.at<cv::Vec3b>(x,y) == cv::Vec3b(255,255,255))
						pixelValue=0;
						if(image.at<cv::Vec3b>(x,y) == cv::Vec3b(0,0,0))
						pixelValue=1;
						else
						pixelValue=0.00001;
						
						if(maxDistance!=0.0)
						{
						realPartition[i][j]+= pixelValue*cos(2*PI*i*(radius/maxDistance)+j*theta);
					    imaginaryPartition[i][j]-= pixelValue*sin(2*PI*i*(radius/maxDistance)+j*theta);
						}
				}
			}
		}
	}
	
	
	for(int i=0;i<maxFrequenceI;i++)
	{
		for(int j=0;j<maxFrequenceJ;j++)
		{
			if(i==0&&j==0&&maxDistance!=0.0)
			FourierCoefficients[0]= sqrt(pow(realPartition[0][0],2)+pow(realPartition[0][0],2)/(PI*pow(maxDistance,2)));				
			else		
			FourierCoefficients[i*maxFrequenceJ+j]=sqrt(pow(realPartition[i][j],2)+pow(imaginaryPartition[i][j],2)/FourierCoefficients[0]);
		}
	}
}
double Fourier::findMaximumDistanceToCentroid(double centroidX,double centroidY,Mat image)
{
	double maxDistance=0;
	
	
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
	      	if(image.at<cv::Vec3b>(i,j) == cv::Vec3b(255,255,255)
	      		||image.at<cv::Vec3b>(i,j) != cv::Vec3b(0,0,0))
	      	{
				double value=EucliedianDistance(i,j,centroidX,centroidY);	      		
	      		if(value>maxDistance)
	      		maxDistance=value;
	      		
	      	}
		}
	}


	return maxDistance;
}
double Fourier::EucliedianDistance(int value1X,int value1Y,int value2X,int value2Y)
{
	double val;

		val=sqrt((value2X-value1X)*(value2X-value1X)+(value2Y-value1Y)*(value2Y-value1Y));

	return val;
}
