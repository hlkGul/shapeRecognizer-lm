#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>
#include <math.h>
#include <iomanip>      // std::setprecision


using namespace cv;
using namespace std;

class huMoments
{
	public:
		huMoments();
		double getHuMoments(int i){return I[i];}
		void calculateCentralAndRawMoments(string filename);
		void calculateHuMoments(double n02,double n03,double n11,double n12,double n20,double n21,double n30);
	private:
		double I[7];

};
