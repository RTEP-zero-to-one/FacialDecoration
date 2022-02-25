
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
int main()
{
	loadCascade();
	VideoCapture capture;
	capture.open(0);
	if (false == capture.isOpened())
	{
		cout << "摄像头没有打开！！！" << endl;
		return -1;
	}
	Mat hat = imread("hat.jpeg");
	while (true) {
		capture >> frame;
		Detect detection;
		detection.faceDetect(frame, cascade_face);
		detection.eyeDetect(frame, cascade_eye);
		detection.getAngle(frame);
		displayDetection(frame, detection);
		Mat test=detection.decorate(frame, hat);
		imshow("ceshi", test);
		waitKey(1);
	}
	capture.release();
	return 0;
}

