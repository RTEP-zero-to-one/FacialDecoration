#include <mythread.h>
#include "global_variable.h"
#include "face_detect.h"
#include "cascade.h"
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <iostream>


using namespace cv;
using namespace std;
Mat frame;
Rect faceRect;
Rect noseRect;
Rect eyeRect;
Rect mouthRect;
void Mythread::run() {
	//capture >> frame;
	Detect detection;
	detection.faceDetect(frame, cascade_face);
	detection.eyeDetect(frame, cascade_eye);
	detection.getAngle(frame);
	displayDetection(frame, detection);
	Mat test = detection.decorate(frame, hat);
	

}