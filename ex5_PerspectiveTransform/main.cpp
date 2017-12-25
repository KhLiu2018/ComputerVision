#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include "PerspectiveTransform.h"
#include "CImg.h"
using namespace std;
using namespace cimg_library;

// four node of a quadrilateral paper
/*
#define X0 648
#define Y0 795
#define X1 2608
#define Y1 922
#define X2 648
#define Y2 3649
#define X3 2505
#define Y3 3519*/

int main(){
    int X0, Y0, X1, Y1, X2, Y2, X3, Y3;
    cout << " (x0, y0) = " << endl;
    cin >> X0 >> Y0;
    cout << " (x1, y1) = " << endl;
    cin >> X1 >> Y1;
    cout << " (x2, y2) = " << endl;
    cin >> X2 >> Y2;
    cout << " (x3, y3) = " << endl;
    cin >> X3 >> Y3;
    CImg<unsigned char> img("2.jpg");
    int img_height = img.height();
    int img_width = img.width();
    CImg<unsigned char> img_trans(img_width, img_height, 1, 3, 0);
    //Mat img_trans = Mat::zeros(img_height,img_width,CV_8UC3);
    PerspectiveTransform temp;
    PerspectiveTransform tansform = temp.quadrilateralToQuadrilateral(0,0,img_width-1,0, 0,img_height-1,
      img_width-1,img_height-1,X0,Y0, X1,Y1, X2,Y2, X3,Y3);

    vector<float> ponits;
    for(int i=0;i<img.height();i++){
        for(int j=0;j<img.width();j++){
            ponits.push_back(j);
            ponits.push_back(i);
        }
    }
    tansform.transformPoints(ponits);

    for(int i = 0; i < img_height; i++){
      //unsigned char *t = img_trans.data(0,0);
        for (int j = 0; j < img_width; j++){
            int tmp = i*img_width+j;
            int x = ponits[tmp*2];
            int y = ponits[tmp*2+1];
            if(x < 0 || x > (img_width-1) || y < 0 || y > (img_height-1))
                continue;
            img_trans(j, i, 0, 0) = img(x, y, 0, 0);
            img_trans(j, i, 0, 1) = img(x, y, 0, 1);
            img_trans(j, i, 0, 2) = img(x, y, 0, 2);

        }
    }
    // Bilinear Interpolation
    int dw = 595;
    int dh = 842;
    CImg<unsigned char> img_BI(dw, dh, 1, 3, 0);
    double rw = double(img_width) / double(dw);
    double rh = double(img_height) / double(dh);

    cimg_forXY(img_BI, x, y) {
      double u = x * rw;
      double v = y * rh;
      int int_u = (int)u;
      int int_v = (int)v;
      double du = u - double(int_u); // decimal part of u
      double dv = v - double(int_v); // decimal part of v

      if (int_u == img_width-1 || int_v == img_height-1) {
        img_BI(x, y, 0, 0) = img_trans(int_u, int_v, 0, 0);
        img_BI(x, y, 0, 1) = img_trans(int_u, int_v, 0, 1);
        img_BI(x, y, 0, 2) = img_trans(int_u, int_v, 0, 2);
      } else {
        img_BI(x, y, 0, 0) = img_trans(int_u, int_v, 0, 0)*(1-du)*(1-dv) + img_trans(int_u+1, int_v, 0, 0)*du*(1-dv) + \
img_trans(int_u+1, int_v+1, 0, 0)*du*dv + img_trans(int_u, int_v+1, 0, 0)*(1-du)*dv;
        img_BI(x, y, 0, 1) = img_trans(int_u, int_v, 0, 1)*(1-du)*(1-dv) + img_trans(int_u+1, int_v, 0, 1)*du*(1-dv) + \
img_trans(int_u+1, int_v+1, 0, 1)*du*dv + img_trans(int_u, int_v+1, 0, 1)*(1-du)*dv;
        img_BI(x, y, 0, 2) = img_trans(int_u, int_v, 0, 2)*(1-du)*(1-dv) + img_trans(int_u+1, int_v, 0, 2)*du*(1-dv) + \
img_trans(int_u+1, int_v+1, 0, 2)*du*dv + img_trans(int_u, int_v+1, 0, 2)*(1-du)*dv;
      }
    }

    img_trans.save("trans.jpg");
    //img_trans.display();
    img_BI.save("bi.jpg");
    img_BI.display();
    return 0;
}
