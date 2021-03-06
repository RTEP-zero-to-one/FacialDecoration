#pragma once
#include "global_variable.h"
#include<opencv2/ml.hpp>

class Detect {
friend void displayDetection(const Mat&,const Detect&);
private:
	int miniScaleFace = 5;
	int miniScaleEye = 2;
	Rect leftEyeRect;
	Rect rightEyeRect;
	Rect faceRect;
	Rect noseRect;
	Rect mouthRect;
	Point leftEyeCenter;
	Point rightEyeCenter;
	int diffY;
	int diffX;
public:
	bool faceDetect(const Mat& src, CascadeClassifier& cascade);
	bool noseDetect(const Mat& src, CascadeClassifier& cascade);
	bool eyeDetect(const Mat& src, CascadeClassifier& cascade);
	bool mouthDetect(const Mat& src, CascadeClassifier& cascade);
	bool getAngle(const Mat& src);
	Mat decorate(const Mat& src, const Mat& res,const Mat&warningRes);
	Mat transform(const Mat& res);
	
};
void displayDetection(const Mat&, const Detect& );
typedef Mat(*pf)(int, const Mat&, const Mat&);
Mat callback(int error_id, const Mat& src, const Mat& res);
Mat errWarning(pf p, int error_id, const Mat& src, const Mat& res);	
