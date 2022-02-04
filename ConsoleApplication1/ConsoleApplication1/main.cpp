// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include "global_variable.h"
#include "face_detect.h"

using namespace std;
using namespace cv;
CascadeClassifier cascade;

Mat frame, imageGray;
int main()
{
	if (!cascade.load(FACE_XML))
	{
		printf("级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！\n");
	}
	VideoCapture capture;
	capture.open(0);
	if (false == capture.isOpened())
	{
		cout << "摄像头没有打开！！！" << endl;
		return -1;
	}
	
	while (true) {
		capture >> frame;
		Rect faceRect;
		faceDetect(frame, cascade, faceRect);
		rectangle(frame, faceRect, Scalar(0, 255, 0), 2);
		imshow("原图像", frame);
		waitKey(1);
	}
	capture.release();
	return 0;
}

