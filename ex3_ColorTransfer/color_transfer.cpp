#include <iostream>
#include <fstream>
#include <cmath>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

void Mean_Variance(CImg<double> img, double mean[], double variance[]) {
  double total = img.width() * img.height();
  double sum[3] = {0.0f};
  cimg_forXYC(img, x, y, c) {
    sum[c] += img(x, y, 0, c);
  }
  for (int i = 0; i < 3; i++) {
    mean[i] = sum[i] / total;
  }
  double sum_variance[3] = {0.0f};
  cimg_forXYC(img, x, y, c) {
    sum_variance[c] += (img(x, y, 0, c) - mean[c]) * (img(x, y, 0, c) - mean[c]);
  }
  for (int i = 0; i < 3; i++) {
    variance[i] = sqrt(sum_variance[i] / total);
  }
}

CImg<unsigned char> ColorTransfer(CImg<unsigned char> img_s, CImg<unsigned char> img_t) {
  CImg<double> s_lab = img_s.get_RGBtoLab();
  //s_lab.display("slab");

  CImg<double> t_lab = img_t.get_RGBtoLab();
  //t_lab.display("tlab");
  double mean_s[3] = {0.0f};
  double mean_t[3] = {0.0f};
  double variance_s[3] = {0.0f};
  double variance_t[3] = {0.0f};
  Mean_Variance(s_lab, mean_s, variance_s);
  Mean_Variance(t_lab, mean_t, variance_t);
  CImg<double> transfer_lab(img_s.width(), img_s.height(), 1, 3);
  double ratio[3];
  for (int i = 0; i < 3; i++) {
    ratio[i] = variance_t[i] / variance_s[i];
  }
  cimg_forXYC(img_s, x, y, c) {
    transfer_lab(x, y, 0, c) = (s_lab(x, y, 0, c) - mean_s[c])*ratio[c] + mean_t[c];
  }

  return transfer_lab.get_LabtoRGB();
}

int main() {
  CImg<unsigned char> img_s("s.jpg");
  CImg<unsigned char> img_t("t.jpg");
  img_s.display("s");
  img_t.display("t");
  CImg<unsigned char> img = ColorTransfer(img_s, img_t);
  img.display("img");
  img.save("img.jpg");
  return 0;
}
