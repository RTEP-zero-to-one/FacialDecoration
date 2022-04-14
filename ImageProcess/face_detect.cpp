# include "face_detect.h"
bool Detect::faceDetect(const Mat& src, CascadeClassifier& cascade)
{
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows / miniScaleFace), cvRound(src.cols / miniScaleFace), CV_8UC1);
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
	int w = miniScaleFace * maxFace.width;
	int h = miniScaleFace * maxFace.height;
	int x = miniScaleFace * (p.x);
	int y = miniScaleFace * (p.y);
	Rect faceLocation(x, y, w, h);
	faceRect = faceLocation;
	return 1;
}
bool Detect::mouthDetect(const Mat& src, CascadeClassifier& cascade)
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
bool Detect::eyeDetect(const Mat & src, CascadeClassifier & cascade)
{
	Mat imgGray;
	Mat srcTemp = src.clone();
	cvtColor(srcTemp, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	Mat imgSmall(cvRound(src.rows / miniScaleEye), cvRound(src.cols / miniScaleEye), CV_8UC1);
	resize(imgGray, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	vector<Rect> eyes;
	cascade.detectMultiScale(imgSmall, eyes, 1.1, 2, 0, Size(30, 30));
	if (eyes.size() < 2) {
		return false;
	}	
	Rect eye1 = eyes[0];
	Rect eye2 = eyes[1];
	Point p1 = eye1.tl();
	int w1 = miniScaleEye * eye1.width;
	int h1 = miniScaleEye* eye1.height;
	int x1 = miniScaleEye * (p1.x);
	int y1 = miniScaleEye * (p1.y);
	Rect eyeLocation1(x1, y1, w1, h1);
	Point p2 = eye2.tl();
	int w2 = miniScaleEye * eye2.width;
	int h2 = miniScaleEye * eye2.height;
	int x2 = miniScaleEye * (p2.x);
	int y2 = miniScaleEye * (p2.y);
	Rect eyeLocation2(x2, y2, w2, h2);
	if (x1 < x2) {
		leftEyeRect=eyeLocation1;
		rightEyeRect=eyeLocation2;
	}
	else {
		rightEyeRect=eyeLocation2;
		leftEyeRect=eyeLocation1;
	}
	return 1;
}
bool Detect::getAngle(const Mat& src) {
	if ((leftEyeRect.area()==0)||(rightEyeRect.area()==0)) {
		return 0;
	}
	Mat img = src.clone();
	Mat eyeLeft = img(leftEyeRect);
	Mat eyeRight = img(rightEyeRect);
	Mat left;
	Mat right;
	int leftX = 0, leftY = 0,leftEyeX=0,leftEyeY=0;
	int countLeft = 0, countRight = 0;
	int rightX = 0, rightY = 0, rightEyeX = 0, rightEyeY = 0;
	cvtColor(eyeLeft, left, COLOR_BGR2GRAY);
	threshold(left, left, 30, 255, THRESH_BINARY);
	cvtColor(eyeRight, right, COLOR_BGR2GRAY);
	threshold(right, right, 30, 255, THRESH_BINARY);

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
	leftEyeCenter.x = leftEyeRect.tl().x + leftEyeX;
	leftEyeCenter.y=leftEyeRect.tl().y + leftEyeY;
	rightEyeCenter.x = rightEyeRect.tl().x + rightEyeX;
	rightEyeCenter.y=rightEyeRect.tl().y + rightEyeY;
	diffY = rightEyeCenter.y - leftEyeCenter.y;          
	diffX= rightEyeCenter.x - leftEyeCenter.x;
	
	return true;
	
}
Mat Detect::decorate(const Mat& src, const Mat& res) {
	if (faceRect.area() == 0||res.empty()) {
		return src;
	}
	Mat img = src.clone();
	int length = res.cols;
	int faceWidth = faceRect.width;
	int faceHeight = faceRect.height;
	Point faceCorner = faceRect.tl();
	float resizeRate = faceWidth*1.3 / length;
	Mat resNew = transform(res);
	resize(resNew, resNew, Size(cvRound(resNew.cols*resizeRate), cvRound(resNew.rows * resizeRate)));
	int lengthofRes=resNew.cols;
	int widthofRes = resNew.rows;	
	int roi_x, roi_y;
	roi_x = cvRound(faceCorner.x - (resNew.cols - faceWidth) / 2); 
	roi_y = cvRound(faceCorner.y- resNew.rows * 0.4);
	//roi_y = cvRound(faceCorner.y - resNew.rows * 1);	
	int diff_x = img.cols - (roi_x + lengthofRes);
	int diff_y = img.rows - (roi_y + widthofRes);
	int diff_roi_x = roi_x;
	int diff_roi_y = roi_y;//
	Rect resROI;
	if (diff_roi_x >= 0 && diff_roi_y >= 0 && diff_x>=0&& diff_y>=0) {
		resROI=Rect(diff_roi_x, diff_roi_y, lengthofRes, widthofRes);
	}
	else {
		if (diff_roi_x >= 0) {
			diff_roi_x = 0;
		}
		if (diff_roi_y >= 0) {
			diff_roi_y = 0;
		}
		if (diff_x >= 0) {
			diff_x = 0;
		}
		if (diff_y >= 0) {
			diff_y = 0;
		}
		resNew(cv::Rect(-diff_roi_x, -diff_roi_y, lengthofRes + diff_x + diff_roi_x, widthofRes + diff_roi_y + diff_y)).copyTo(resNew);
		lengthofRes = resNew.cols;
		widthofRes = resNew.rows;
		resROI=Rect(roi_x - diff_roi_x, roi_y - diff_roi_y, lengthofRes, widthofRes);
	}
	//Mat resGray;
	//Mat resMask;
	//Mat resMaskBlack;
	//Mat resFinal;
	//cv::cvtColor(resNew, resGray, COLOR_BGR2GRAY);

	//cv::threshold(resGray, resMaskBlack, 10, 255, THRESH_BINARY);
	//cv::bitwise_not(resMaskBlack, resMaskBlack);
	//cv::bitwise_or(resMaskBlack, resGray,resFinal);

	//cv::threshold(resFinal, resMask, 220, 255, THRESH_BINARY);
	//cv::bitwise_not(resMask, resMask);
	Mat imageROI = img(resROI);
	//Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	//Mat resMaskk;
	//erode(resMask, resMaskk, element);
	resNew.copyTo(imageROI, resNew);

	//resNew.copyTo(imageROI, resMaskk);
	return img;
}
Mat Detect::transform(const Mat& res) {
	if (diffX == 0 || diffY == 0) {
		return res;
	}
	float eyeTan =(diffY*1.0)/(diffX*1.0);
//	cout << eyeTan << endl;
	float eyeAngle = atan(eyeTan) * 180.0/ 3.14159*(-1);
	Point2f center(res.cols / 2, res.rows / 2);//中心
	Mat M = getRotationMatrix2D(center, eyeAngle, 1); 
	Mat resNew;
	warpAffine(res, resNew, M, Size(res.cols, res.rows));
	return resNew;
	
}

bool Detect::noseDetect(const Mat& src, CascadeClassifier& cascade)
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
void displayDetection(const Mat& src, const Detect& detection) {
	Mat frame = src.clone();
	if (detection.leftEyeRect.area()) {
		rectangle(frame, detection.leftEyeRect, Scalar(0, 255, 0), 2);
	}
	if (detection.rightEyeRect.area()) {
		rectangle(frame, detection.rightEyeRect, Scalar(0, 255, 0), 2);
	}
	if (detection.faceRect.area()) {
		rectangle(frame, detection.faceRect, Scalar(0, 0, 255), 2);
	}
	circle(frame, detection.leftEyeCenter, 3, Scalar(0, 0, 255), 3, 8);
	circle(frame, detection.rightEyeCenter, 3, Scalar(0, 0, 255), 3, 8);
	imshow("Detection Result", frame);
}
