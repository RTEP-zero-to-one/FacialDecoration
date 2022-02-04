#pragma once
#include <opencv2/opencv.hpp>
#include<opencv2/ml.hpp>
using namespace cv;
extern CascadeClassifier cascade_face;
extern CascadeClassifier cascade_nose;
extern CascadeClassifier cascade_mouth;
extern CascadeClassifier cascade_eye;
extern Mat frame;
#define FACE_XML "face_detect.xml"
#define NOSE_XML "nose_detect.xml"
#define EYE_XML "eye_detect.xml"
#define MOUTH_XML "mouth_detect.xml"