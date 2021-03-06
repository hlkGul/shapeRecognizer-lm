#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>

using namespace cv;
using namespace std;


class statisticalDescriptor
{
	public:
	
	double EucliedianDistance(int value1X,int value1Y,int value2X,int value2Y);
	void StatisticalDescriptor(string filename);
	Point MaxDistanceFromCentroidToContour(double centroidX,double centroidY,Mat gray);
	double getRatesPerSquare(int i){return rates[i];}

	private:
	double rates[10];		
	
};
