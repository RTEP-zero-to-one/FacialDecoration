# include "face_detect.h"
bool faceDetect(Mat& src, CascadeClassifier& cascade,  Rect& faceRect)
{
	int scale = 5;
	Mat imgGray;//灰度图
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);//转为灰度图
	equalizeHist(imgGray, imgGray);//直方图均衡化，增加对比度方便处理
	Mat imgSmall(cvRound(src.rows / scale), cvRound(src.cols / scale), CV_8UC1);//按比例缩小
	resize(imgGray, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	vector<Rect>faces;
	Rect maxFace;
	cascade.detectMultiScale(imgSmall, faces, 1.1, 2, 0, Size(30, 30));
	if (faces.size() == 0)
	{
		return false;
	}

	double maxArea = 0;
	int maxIndex = 0;

	for (int i = 0; i < faces.size(); i++)
	{
		double area = faces[i].area();
		if (area > maxArea)
		{
			maxIndex = i;
			maxArea = area;
		}
	}
	maxFace = faces[maxIndex];//---------------------------------得到最大的矩形框
	Point p = maxFace.tl();
	int w = scale * maxFace.width;//原图中的宽度
	int h = scale * maxFace.height;//原图中的高度
	int x = scale * (p.x);//原图中的左上角
	int y = scale * (p.y);//原图中的右上角
	Rect faceLocation(x, y, w, h);
	faceRect = faceLocation;
	return 1;
}