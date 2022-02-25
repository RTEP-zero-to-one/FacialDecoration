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
	diffY = rightEyeCenter.y - leftEyeCenter.y;            //右眼比左眼高的值
	diffX= rightEyeCenter.x - leftEyeCenter.x;
	/*
	if (faceRect.area() == 0) {
		return false;
	}
	
	int sum_err = 0;
	int start_y, end_y;
	Mat faceRoi = img(faceRect);
	start_y = 0.5 * faceRoi.rows - 10;
	if (start_y < 0) {
		start_y = 0;
	}
	
	end_y = 0.5 * faceRoi.rows + 10;
	if (end_y >faceRoi.rows) {
		end_y = faceRoi.rows;
	}
	vector<int> face_left(end_y - start_y), face_right(end_y - start_y), face_err(end_y - start_y);
	cvtColor(faceRoi, faceRoi, COLOR_BGR2YCrCb);
	int crmax = 173;
	int crmin = 133;
	int cbmax = 127;
	int cbmin = 77;
	for (int i = start_y; i < end_y; i++)
	{
		for (int j = 0; j < faceRoi.cols; j++) {
			if ((faceRoi.at<Vec3b>(i, j)[1] > crmax) || (faceRoi.at<Vec3b>(i, j)[1] < crmin)
				|| (faceRoi.at<Vec3b>(i, j)[2] > cbmax) || (faceRoi.at<Vec3b>(i, j)[2] < cbmin))
				;
			else {
				face_left[i - start_y] = j;
				break;
			}
		}
		for (int j = faceRoi.cols-1; j > 0; j--) {
			if ((faceRoi.at<Vec3b>(i, j)[1] > crmax) || (faceRoi.at<Vec3b>(i, j)[1] < crmin)
				|| (faceRoi.at<Vec3b>(i, j)[2] > cbmax) || (faceRoi.at<Vec3b>(i, j)[2] < cbmin))
				;
			else {
				face_right[i - start_y] = faceRoi.cols - j;
				break;
			}
		}
		face_err[i - start_y] = face_left[i - start_y] - face_right[i - start_y];
		sum_err += face_err[i - start_y];
	}

	diffX = sum_err / (end_y - start_y);                        // > 0 : 左多右少
	
	if (abs(diffX) <= 25) {
		diffX = 0;
	}
	if (abs(diffY) <= 10) {
		diffY = 0;
	}*/
	return true;
	
}
Mat Detect::decorate(const Mat& src, const Mat& res) {
	if (faceRect.area() == 0) {
		return src;
	}
	int length = res.cols;
	int faceLength = faceRect.width;
	float resizeRate = faceLength*1.5 / length;
	Mat resNew = transform(res);
	resize(resNew, resNew, Size(cvRound(resNew.cols*resizeRate), cvRound(resNew.rows * resizeRate)));
	return resNew;
}
Mat Detect::transform(const Mat& res) {
	if (diffX == 0 || diffY == 0) {
		return res;
	}
	float eyeTan =(diffY*1.0)/(diffX*1.0);
	cout << eyeTan << endl;
	float eyeAngle = atan(eyeTan) * 180.0/ 3.14159*(-1);
	Point2f center(res.cols / 2, res.rows / 2);//中心
	Mat M = getRotationMatrix2D(center, eyeAngle, 1);//计算旋转的仿射变换矩阵 
	Mat resNew;
	warpAffine(res, resNew, M, Size(res.cols, res.rows));//仿射变换
	return resNew;
	
}
/*
Mat Detect::perspectiveTrans(const Mat& res) {
	Mat kernal(3, 3, CV_32FC1);
	Mat res_new;

	kernal = getKernal(res);

	if (flag) {////////////报错
			warpPerspective(res, res_new, kernal, cv::Size(out_width, out_height), 1, 0, Scalar(0, 0, 0));
		return res_new;
	}
	else
		return res;

}

Mat Detect::getKernal(const Mat& res) {//传入一个要贴的素材图片，返回3*3的矩阵
	int max1 = 50, max3 = 50;        //1要跳跃
	if (!diffX && !diffY)
		return (cv::Mat_<float>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0);
	    flag = false;
	if (diffX > max1)
		diffX = max1;
	else if (diffX < -max1)
		diffX = -max1;
	if (diffY > max3)
		diffY = max3;
	else if (diffY < -max3)
		diffY = -max3;
	int cols = res.cols;
	int rows = res.rows;
	float anx, any, anz;
	anx = -0.002 * diffX;   //x边动，y中轴不变
	any = 0;
	vector<cv::Point2f> corners(4), corners_trans(4);
	corners[0] = cv::Point2f(0, 0);
	corners[1] = cv::Point2f(cols - 1, 0);
	corners[2] = cv::Point2f(cols - 1, rows - 1);
	corners[3] = cv::Point2f(0, rows - 1);
	corners_trans[0] = cv::Point2f(0, 0);
	corners_trans[1] = cv::Point2f(cols - 1, 0);
	corners_trans[2] = cv::Point2f(cols - 1, rows - 1);
	corners_trans[3] = cv::Point2f(0, rows - 1);

	if (diffX) {

		int dis_x, dis_y, dis_xx1, dis_yy1, dis_xx2, dis_yy2;
		dis_x = 0.5 * rows * cos(any) * sin(any);
		dis_y = 0.5 * res.rows * cos(any) * cos(any);
		dis_xx1 = 0.5 * (cols + 2 * dis_x) * cos(anx) * cos(anx);
		dis_yy1 = 0.5 * (cols + 2 * dis_x) * cos(anx) * sin(anx);
		dis_xx2 = 0.5 * (cols - 2 * dis_x) * cos(anx) * cos(anx);
		dis_yy2 = 0.5 * (cols - 2 * dis_x) * cos(anx) * sin(anx);

		corners_trans[0].x = 0.5 * cols - dis_xx2;
		corners_trans[0].y = (0.5 * rows - dis_y) - dis_yy2;

		corners_trans[1].x = 0.5 * cols + dis_xx2;
		corners_trans[1].y = (0.5 * rows - dis_y) + dis_yy2;

		corners_trans[2].x = 0.5 * cols + dis_xx1;
		corners_trans[2].y = rows - (dis_yy1 + (0.5 * rows - dis_y));

		corners_trans[3].x = 0.5 * cols - dis_xx1;
		corners_trans[3].y = rows + (dis_yy1 - (0.5 * rows - dis_y));
	}

		//这里增加旋转角度（中心点旋转：外切矩形中心）
	if (diffY)
	{
		anz = -0.017 * diffY;
			//               cout << "z "<<anz <<endl;
		double an[4];
		float r[4];
		Point2f rot_center = Point2f(0.5 * cols, 0.5 * rows);
		for (int i = 0; i < 4; i++) {
				//以旋转中心为原点,即center平移到现原点
			corners_trans[i] -= rot_center;
				//极坐标，这里以y顺时针旋转
			an[i] = atan2(corners_trans[i].x, corners_trans[i].y);
				//cout << an[i] <<endl;
			r[i] = sqrt((corners_trans[i].y * corners_trans[i].y) + (corners_trans[i].x * corners_trans[i].x));

				//算旋转之后的角度
			an[i] += anz;
				//算旋转之后的x,y坐标
			corners_trans[i].x = r[i] * sin(an[i]);
			corners_trans[i].y = r[i] * cos(an[i]);
				//还原到原理的原点
			corners_trans[i] += rot_center;
		}
	}

		//求正外切矩形
	Point2f change_point = Point2f(0, 0);
	int max_x = cols, min_x = 0, max_y = rows, min_y = 0;
	int max_x_i = -1, min_x_i = -1, max_y_i = -1, min_y_i = -1;
	for (int i = 0; i < 4; i++) {
		if (corners_trans[i].x >= max_x) {
			max_x = corners_trans[i].x;
			max_x_i = i;
		}
		else if (corners_trans[i].x <= min_x) {
			min_x = corners_trans[i].x;
			min_x_i = i;
		}
		if (corners_trans[i].y >= max_y) {
			max_y = corners_trans[i].y;
			max_y_i = i;
		}
		else if (corners_trans[i].y <= min_y) {
			min_y = corners_trans[i].y;
			min_y_i = i;
		}
	}
	if (min_y_i >= 0) {
		change_point.y = -min_y;
	}
	if (min_x_i >= 0) {
		change_point.x = -min_x;
	}
	out_width = max_x - min_x;
	out_height = max_y - min_y;
	for (int i = 0; i < 4; i++) {
		corners_trans[i] += change_point;
	}
	Mat kernal = getPerspectiveTransform(corners, corners_trans);
	flag = true;
	return  kernal;
}
*/
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