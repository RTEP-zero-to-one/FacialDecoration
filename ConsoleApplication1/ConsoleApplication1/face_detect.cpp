# include "face_detect.h"
bool faceDetect(Mat& src, CascadeClassifier& cascade,  Rect& faceRect)
{
	int scale = 5;
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows / scale), cvRound(src.cols / scale), CV_8UC1);
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
	maxFace = faces[maxIndex];
	Point p = maxFace.tl();
	int w = scale * maxFace.width;
	int h = scale * maxFace.height;
	int x = scale * (p.x);
	int y = scale * (p.y);
	Rect faceLocation(x, y, w, h);
	faceRect = faceLocation;
	return 1;
}