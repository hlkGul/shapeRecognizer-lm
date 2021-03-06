#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>

#define PI 3.14159

using namespace cv;
using namespace std;

class Fourier
{
	public:
		Fourier();
		double EucliedianDistance(int value1X,int value1Y,int value2X,int value2Y);
		void FourierDescriptor(string filename);
		double findMaximumDistanceToCentroid(double centroidX,double centroidY,Mat image);
		double getFourierCoefficient(int i);

	private:
		double FourierCoefficients[25];
};
