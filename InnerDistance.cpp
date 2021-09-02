#include "InnerDistance.h"

Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


InnerDistance::InnerDistance()
{	
}

void InnerDistance::InnerDistanceCalculate(string name)
{
	VideoCapture cap(name);
	Mat img,imgHSV,imgThreshold;
	double value[100000],value2[100000];
	cap>>img;
    
   	/// Convert image to gray and blur it
  	cvtColor( img, src_gray, CV_BGR2GRAY );
  	blur( src_gray, src_gray, Size(3,3) );

	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
	findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0) );

	for(int i=0;i<100000;i++)
	{
		value[i]=0;	
		value2[i]=0;	
	}
	
	int degerX[100],degerY[100],sum=0;
	double max=0;
	double newValue;
	int index=0;
	
	for(int i=0;i<contours.size();i++)
	{
			for(int j=0;j<contours[i].size();j++)
			{
				for(int k=0;k<contours[i].size();k++)
				{
					value[index]+=EucliedianDistance((contours[i][j].x),(contours[i][j].y),(contours[i][k].x),(contours[i][k].y));
					value2[index]+=EucliedianDistance((contours[i][j].x),(contours[i][j].y),(contours[i][k].x),(contours[i][k].y));
				}
				index++;
			}
	}
	
	int minimum,temp;
	for(int i=0;i<index-1;i++)
	{
		minimum=i;	
		for(int j=i+1;j<index;j++)
		{
			if(value[j]<value[minimum])
			{
				minimum=j;
			}
		}
		
		if(minimum!=i)
		{
			temp= value[i];
			value[i]=value[minimum];
			value[minimum]=temp;
		}
	}



	int maximum,tempMax;
	for(int i=0;i<index-1;i++)
	{
		maximum=i;	
		for(int j=i+1;j<index;j++)
		{
			if(value2[j]>value2[maximum])
			{
				maximum=j;
			}
		}
		
		if(maximum!=i)
		{
			tempMax= value2[i];
			value2[i]=value2[maximum];
			value2[maximum]=tempMax;
		}
	}

	double partition=(value2[maximum]-value[minimum])/5;	

	distances2[0]=value2[maximum];
	distances2[4]=value[minimum];	

	for(int i=1;i<4;i++)
	{	
		distances2[i]=value2[maximum]-i*partition;
	}			
		
	// En üst,en sol, en sağ ,en alt noktalarin birbirlerine olan uzaklıklar toplamı
	double minvalX=10000,minvalIndexX=0,minXdependY=0;	
	double maxvalX=-10000,maxvalIndexX=0,maxXdependY=0;
	int minvalY=10000,minvalIndexY=0,minYdependX=0;	
	int maxvalY=-10000,maxvalIndexY=0,maxYdependX=0;
	int valueResult[6];	
	
	
	
	
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

	distances1[0]=EucliedianDistance(minvalX,minXdependY,maxvalX,maxXdependY);
	distances1[1]=EucliedianDistance(minvalX,minXdependY,minYdependX,minvalY);
	distances1[2]=EucliedianDistance(minvalX,minXdependY,maxYdependX,maxvalY);
	distances1[3]=EucliedianDistance(maxvalX,maxXdependY,maxYdependX,maxvalY);
	distances1[4]=EucliedianDistance(maxvalX,maxXdependY,minYdependX,minvalY);
	distances1[5]=EucliedianDistance(maxvalY,maxYdependX,minYdependX,minvalY);

}
double InnerDistance::EucliedianDistance(int value1X,int value1Y,int value2X,int value2Y)
{
	int val;

		val=sqrt((value2X-value1X)*(value2X-value1X)+(value2Y-value1Y)*(value2Y-value1Y));

	return val;
}
