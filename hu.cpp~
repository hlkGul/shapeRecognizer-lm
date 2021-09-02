#include "hu.h"

huMoments::huMoments()
{
	
}

void huMoments::calculateCentralAndRawMoments(string filename)
{
	Mat src;
	double n02,n03,n11,n12,n20,n21,n30;	
	double n02gama,n03gama,n11gama,n12gama,n20gama,n21gama,n30gama;
	

	// Central Moments
	double mc00=0.0,mc02=0.0,mc03=0.0,mc11=0.0,mc12=0.0,mc20=0.0,mc21=0.0,mc30=0.0;
	double m00=0.0,m01=0.0,m10=0.0,m00div=0.0;
	double xc=0.0,yc=0.0;
	double gama02=0.0,gama03=0.0,gama11=0.0,gama12=0.0,gama20=0.0,gama21=0.0,gama30=0.0;	
	

	VideoCapture cap(filename);

  	/// Load image
  	cap>>src; 

	if( !src.data )
    { return; }
    
    double matrix[src.rows][src.cols];
	
	for(int i = 0;i < src.rows ;i++){
        for(int j = 0;j < src.cols ;j++){
        
 			if(src.at<cv::Vec3b>(i,j) == cv::Vec3b(255,255,255))       	
 			matrix[i][j]=1.0;
 			else if(src.at<cv::Vec3b>(i,j) == cv::Vec3b(0,0,0))       	
 			matrix[i][j]=0.0;
 			else
 			matrix[i][j]=0.01;
        }
    }
	
	
	for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			m00+=pow(i,0)*pow(j,0)*matrix[i][j];
			m10+=pow(i,1)*pow(j,0)*matrix[i][j];
			m01+=pow(i,0)*pow(j,1)*matrix[i][j];
		}
	}
	

	xc=m10/m00;
	yc=m01/m00;
	
	
	for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			mc00+= pow(i-xc,0)*pow(j-yc,0)*matrix[i][j];
			mc02+= pow(i-xc,0)*pow(j-yc,2)*matrix[i][j];
			mc03+= pow(i-xc,0)*pow(j-yc,3)*matrix[i][j];
			mc11+= pow(i-xc,1)*pow(j-yc,1)*matrix[i][j];
			mc12+= pow(i-xc,1)*pow(j-yc,2)*matrix[i][j];
			mc20+= pow(i-xc,2)*pow(j-yc,0)*matrix[i][j];
			mc21+= pow(i-xc,2)*pow(j-yc,1)*matrix[i][j];
			mc30+= pow(i-xc,3)*pow(j-yc,0)*matrix[i][j];
		}
	}
	
	
	gama02= ((static_cast<double>(0+2))/2)+1.0;
	gama03= ((static_cast<double>(0+3))/2)+1.0;
	gama11= ((static_cast<double>(1+1))/2)+1.0;
	gama12= ((static_cast<double>(1+2))/2)+1.0;
	gama20= ((static_cast<double>(2+0))/2)+1.0;
	gama21= ((static_cast<double>(2+1))/2)+1.0;
	gama30= ((static_cast<double>(3+0))/2)+1.0;
	
	
	n02gama=pow(mc00,gama02);
	n03gama=pow(mc00,gama03);
	n11gama=pow(mc00,gama11);
	n12gama=pow(mc00,gama12);	
	n20gama=pow(mc00,gama20);
	n21gama=pow(mc00,gama21);
	n30gama=pow(mc00,gama30);
	



	n02= mc02/n02gama;	
	n03= mc03/n03gama;
	n11= mc11/n11gama;
	n12= mc12/n12gama;
	n20= mc20/n20gama; 	
	n21= mc21/n21gama;
	n30= mc30/n30gama;
	
	 calculateHuMoments(n02,n03,n11,n12,n20,n21,n30);
	
}
void huMoments::calculateHuMoments(double n02,double n03,double n11,double n12,double n20,double n21,double n30)
{
		
	// Hu invariant moments
	
	I[1]= n20+n02;
	I[2]= pow((n20-n02),2)+ 4*pow(n11,2);
	I[3]= pow((n30-3*n12),2)+ pow((3*n21-n03),2);
	I[4]= pow((n30+n12),2)+ pow((n21+n03),2);
	I[5]= (n30-3*n12)*(n30+n12)*(pow((n30+n12),2)-3*pow((n21+n03),2))+(3*n21-n03)*(n21+n03)*(3*pow((n30+n12),2)-pow((n21+n03),2));
	I[6]= (n20-n02)*(pow((n30+n12),2)-pow((n21+n03),2))+4*n11*(n30+n12)*(n21+n03);
	I[7]= (3*n21-n03)*(n30+n12)*(pow((n30+n12),2)-3*pow((n21+n03),2))+(n30-3*n12)*(n21+n03)*(3*pow((n30+n12),2)-pow((n21+n03),2));
			
}
