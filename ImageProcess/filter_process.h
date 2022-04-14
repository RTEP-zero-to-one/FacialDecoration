#pragma once
#include "global_variable.h"
Mat filter(Mat& src, int style_num);
Mat whiteFace(const Mat& src, int degree);
Mat faceBlur(const Mat& src, int filterVal);
