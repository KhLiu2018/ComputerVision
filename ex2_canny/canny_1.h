#ifndef _CANNY_
#define _CANNY_
#include "CImg.h"
#include <vector>
#include <string>

using namespace std;
using namespace cimg_library;

class canny {
private:
  CImg<unsigned char> img;  //Original Image
  CImg<unsigned char> grayscaled;  // Grayscale
  CImg<unsigned char> gFiltered;  // Gaussian Filter
  CImg<unsigned char> sFiltered;  //Sobel Filtered
  vector<vector<double> > angles;  //Angle Map
  CImg<unsigned char> non;  // Non-maxima supp.
  CImg<unsigned char> thres; //Double threshold and final

public:
  canny(const char*);  //Constructor
  CImg<unsigned char> toGrayScale();
  vector<vector<double> > createFilter(int, int, double);  //Creates a gaussian filter
  CImg<unsigned char> useFilter(CImg<unsigned char>, vector<vector<double> >);
  CImg<unsigned char> sobel(); //Sobel filtering
  CImg<unsigned char> nonMaxSupp(); //Non-maxima supp.
  CImg<unsigned char> threshold(CImg<unsigned char>, int, int); //Double threshold and finalize picture
};

#endif
