#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>
#include "canny_1.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main() {
    const char *filePath = "2.jpg"; //Filepath of input image
    canny cny(filePath);
    return 0;
}
