#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>

using namespace cv;
using namespace std;

class Histogram
{
	public:
		Histogram();
		void histogramCoding(string filename);
		double getBlackRate(){return blackRate;}
		double getWhiteRate(){return whiteRate;}
	private:
		double blackRate;
		double whiteRate;

};
