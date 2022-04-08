#pragma once
#include <opencv2/opencv.hpp>
#include<opencv2/ml.hpp>
#include "cascade.h"
#include <iostream>
using namespace cv;
using namespace std;
extern CascadeClassifier cascade_face;
extern CascadeClassifier cascade_nose;
extern CascadeClassifier cascade_mouth;
extern CascadeClassifier cascade_eye;
extern Mat frame;
extern Rect faceRect;
extern Rect noseRect;
extern Rect eyeRect;
extern Rect mouthRect;
extern Mat hat;
#define FACE_XML "assets/face_detect.xml"
#define NOSE_XML "assets/nose_detect.xml"
#define EYE_XML "assets/haarcascade_eye_tree_eyeglasses.xml"
#define MOUTH_XML "assets/mouth_detect.xml"
#define OLDFASHION 1
#define COMICBOOK 2
#define FANTASY 3
#define FREEZE 4
#define MINISCALE 5
#define DARKTONE 6
#define SKETCH 7
