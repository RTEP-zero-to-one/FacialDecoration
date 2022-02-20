#pragma once
#include "global_variable.h"
#include<opencv2/ml.hpp>

bool faceDetect(const Mat& src, CascadeClassifier& cascade, Rect& faceRect);
bool noseDetect(const Mat& src, CascadeClassifier& cascade, Rect& noseRect);
bool eyeDetect(const Mat& src, CascadeClassifier& cascade, vector<Rect>& eyeRect);
bool mouthDetect(const Mat& src,  CascadeClassifier& cascade, Rect& mouthRect);
bool getAngle(const Mat& src, vector<Rect>& eyeRect);