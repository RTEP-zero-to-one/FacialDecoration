
#include "global_variable.h"
#include "face_detect.h"
#include "cascade.h"
#include <opencv2/opencv.hpp>
#include<opencv2/ml.hpp>
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
	while (true) {
		capture >> frame;
		//faceDetect(frame, cascade_face, faceRect);
		//mouthDetect(frame, cascade_mouth, mouthRect);
		eyeDetect(frame, cascade_eye, eyeRect);
		//noseDetect(frame, cascade_nose, noseRect);
		rectangle(frame, eyeRect, Scalar(0, 255, 0), 2);
		imshow("原图像", frame);
		waitKey(1);
	}
	capture.release();
	return 0;
}

