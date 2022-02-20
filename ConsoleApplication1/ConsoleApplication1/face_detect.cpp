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
bool eyeDetect(const Mat& src, CascadeClassifier& cascade, vector<Rect> & eyeRect)
{
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows / MINISCALE), cvRound(src.cols / MINISCALE), CV_8UC1);
	resize(imgGray, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	vector<Rect> eyes;
	cascade.detectMultiScale(imgSmall, eyes, 1.1, 2, 0, Size(30, 30));
	cout << eyes.size() << endl;
	if (eyes.size() < 2)
	{
		cout << "zhaobudao" << endl;
		return false;
	}
	
	
	Rect eye1 = eyes[0];
	Rect eye2 = eyes[1];
	Point p1 = eye1.tl();
	int w1 = MINISCALE * eye1.width;
	int h1 = MINISCALE * eye1.height;
	int x1 = MINISCALE * (p1.x);
	int y1 = MINISCALE * (p1.y);
	Rect eyeLocation1(x1, y1, w1, h1);
	Point p2 = eye2.tl();
	int w2 = MINISCALE * eye2.width;
	int h2 = MINISCALE * eye2.height;
	int x2 = MINISCALE * (p2.x);
	int y2 = MINISCALE * (p2.y);
	Rect eyeLocation2(x2, y2, w2, h2);
	if (x1 < x2) {
		eyeRect.push_back(eyeLocation1);
		eyeRect.push_back(eyeLocation2);
	}
	else {
		eyeRect.push_back(eyeLocation2);
		eyeRect.push_back(eyeLocation1);
	}
	rectangle(src, eyeLocation1, Scalar(0, 255, 0), 2);
	rectangle(src, eyeLocation2, Scalar(0, 255, 0), 2);
	return 1;
}
bool getAngle(const Mat& src, vector<Rect>& eyeRect) {
	if (!eyeRect.size()) {
		return 0;
	}
	Mat img = src.clone();
	Mat eyeLeft = img(eyeRect[0]);
	Mat eyeRight = img(eyeRect[1]);
	Mat left;
	Mat right;
	int leftX = 0, leftY = 0,leftEyeX=0,leftEyeY=0;
	int countLeft = 0, countRight = 0;
	int rightX = 0, rightY = 0, rightEyeX = 0, rightEyeY = 0;
	cvtColor(eyeLeft, left, COLOR_BGR2GRAY);
	threshold(left, left, 30, 255, THRESH_BINARY);
	cvtColor(eyeRight, right, COLOR_BGR2GRAY);
	threshold(right, right, 30, 255, THRESH_BINARY);
	imshow("left",left);
	imshow("right",right);

	
	for (int i = 0; i < left.cols; i++)
		for (int j = 0; j < left.rows; j++) {
			if (left.at<uchar>(i, j)!=0) {
				leftX += i;
				leftY += j;
				countLeft++;
			}
		}
	if (countLeft) {	
		leftEyeX = leftX / countLeft;
		leftEyeY = leftY / countLeft;
	}
	for (int i= 0; i < right.cols; i++)
		for (int j = 0; j < right.rows; j++) {
			if (right.at<uchar>(i, j)!=0) {
				rightX += i;
				rightY += j;
				countRight++;
			}
		}
	if (countRight > 0) {	
		rightEyeX = rightX / countRight;
		rightEyeY= rightY / countRight;
	}
	Point leftEyePos(eyeRect[0].tl().x + leftEyeX, eyeRect[0].tl().y + leftEyeY);
	Point rightEyePos(eyeRect[1].tl().x + rightEyeX, eyeRect[1].tl().y + rightEyeY);
	return true;
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