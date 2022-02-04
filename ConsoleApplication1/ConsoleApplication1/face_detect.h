#pragma once
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

bool faceDetect(Mat& src, CascadeClassifier& cascade, Rect& faceRect);