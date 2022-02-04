# include "face_detect.h"
bool faceDetect(Mat& src, CascadeClassifier& cascade,  Rect& faceRect)
{
	int scale = 5;
	//Mat imgGray;//灰度图
	Mat srcTemp = src.clone();
	Mat imgSmall(cvRound(srcTemp.rows / scale), cvRound(srcTemp.cols / scale), CV_8UC1);//按比例缩小
	resize(srcTemp, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	equalizeHist(imgSmall, imgSmall);//直方图均匀化
	vector<Rect>faces;
	Rect maxFace;
	//cover = Mat::zeros(src.size(), CV_8UC1);//----------------------------------纯黑
	//cover.setTo(255);
	//dst = src.clone();
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
	//faceLocation &= Rect(0, 0, src.cols, src.rows);
	faceRect = faceLocation;
	//rectangle(dst, faceLocation, Scalar(0, 255, 0), 2);
	//rectangle(cover, faceLocation, Scalar(0, 0, 0), -1);//--------------------掩膜
	return 1;
}