#pragma once
#include <opencv2/opencv.hpp>
#include<opencv2\ml.hpp>
using namespace cv;
extern CascadeClassifier cascade;
extern Mat frame;
#define FACE_XML "face_detect.xml"