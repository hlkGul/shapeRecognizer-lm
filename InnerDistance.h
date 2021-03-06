#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>

using namespace cv;
using namespace std;


class InnerDistance
{
	public:
		InnerDistance();
		void InnerDistanceCalculate(string name);
		double getDistances1(int i){ return distances1[i];}
		double getDistances2(int i){ return distances2[i];}
		double EucliedianDistance(int value1X,int value1Y,int value2X,int value2Y);
	private:
		double distances1[6];
		double distances2[5];
};
