# include "face_detect.h"
bool faceDetect(const Mat& src, CascadeClassifier& cascade,  Rect& faceRect)
{
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows /MINISCALE), cvRound(src.cols / MINISCALE), CV_8UC1);
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
	int w = MINISCALE * maxFace.width;
	int h = MINISCALE * maxFace.height;
	int x = MINISCALE * (p.x);
	int y = MINISCALE * (p.y);
	Rect faceLocation(x, y, w, h);
	faceRect = faceLocation;
	return 1;
}
bool mouthDetect(const Mat& src, CascadeClassifier& cascade, Rect& mouthRect)
{
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows / MINISCALE), cvRound(src.cols / MINISCALE), CV_8UC1);
	resize(imgGray, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	vector<Rect> mouths;
	Rect maxMouth;
	cascade.detectMultiScale(imgSmall, mouths, 1.1, 2, 0, Size(30, 30));
	if (mouths.size() == 0)
	{
		return false;
	}

	double maxArea = 0;
	int maxIndex = 0;

	for (int i = 0; i < mouths.size(); i++)
	{
		double area = mouths[i].area();
		if (area > maxArea)
		{
			maxIndex = i;
			maxArea = area;
		}
	}
	maxMouth = mouths[maxIndex];
	Point p = maxMouth.tl();
	int w = MINISCALE * maxMouth.width;
	int h = MINISCALE * maxMouth.height;
	int x = MINISCALE * (p.x);
	int y = MINISCALE * (p.y);
	Rect mouthLocation(x, y, w, h);
	mouthRect = mouthLocation;
	return 1;
}
bool eyeDetect(const Mat& src, CascadeClassifier& cascade, Rect& eyeRect)
{
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows / MINISCALE), cvRound(src.cols / MINISCALE), CV_8UC1);
	resize(imgGray, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	vector<Rect> eyes;
	Rect maxEye;
	cascade.detectMultiScale(imgSmall, eyes, 1.1, 2, 0, Size(30, 30));
	if (eyes.size() == 0)
	{
		cout << "zhaobudao" << endl;
		return false;
	}

	double maxArea = 0;
	int maxIndex = 0;

	for (int i = 0; i < eyes.size(); i++)
	{
		double area = eyes[i].area();
		if (area > maxArea)
		{
			maxIndex = i;
			maxArea = area;
		}
	}
	maxEye = eyes[maxIndex];
	Point p = maxEye.tl();
	int w = MINISCALE * maxEye.width;
	int h = MINISCALE * maxEye.height;
	int x = MINISCALE * (p.x);
	int y = MINISCALE * (p.y);
	Rect eyeLocation(x, y, w, h);
	eyeRect = eyeLocation;
	return 1;
}
bool noseDetect(const Mat& src, CascadeClassifier& cascade, Rect& noseRect)
{
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows / MINISCALE), cvRound(src.cols / MINISCALE), CV_8UC1);
	resize(imgGray, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	vector<Rect> noses;
	Rect maxNose;
	cascade.detectMultiScale(imgSmall, noses, 1.1, 2, 0, Size(30, 30));
	if (noses.size() == 0)
	{
		return 0;
	}

	double maxArea = 0;
	int maxIndex = 0;

	for (int i = 0; i < noses.size(); i++)
	{
		double area = noses[i].area();
		if (area > maxArea)
		{
			maxIndex = i;
			maxArea = area;
		}
	}
	maxNose = noses[maxIndex];
	Point p = maxNose.tl();
	int w = MINISCALE * maxNose.width;
	int h = MINISCALE * maxNose.height;
	int x = MINISCALE * (p.x);
	int y = MINISCALE * (p.y);
	Rect noseLocation(x, y, w, h);
	noseRect = noseLocation;
	return 1;
}