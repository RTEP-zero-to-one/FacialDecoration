# include "face_detect.h"
bool faceDetect(Mat& src, CascadeClassifier& cascade,  Rect& faceRect)
{
	int scale = 5;
	//Mat imgGray;//�Ҷ�ͼ
	Mat srcTemp = src.clone();
	Mat imgSmall(cvRound(srcTemp.rows / scale), cvRound(srcTemp.cols / scale), CV_8UC1);//��������С
	resize(srcTemp, imgSmall, imgSmall.size(), 0, 0, INTER_LINEAR);
	equalizeHist(imgSmall, imgSmall);//ֱ��ͼ���Ȼ�
	vector<Rect>faces;
	Rect maxFace;
	//cover = Mat::zeros(src.size(), CV_8UC1);//----------------------------------����
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
	maxFace = faces[maxIndex];//---------------------------------�õ����ľ��ο�
	Point p = maxFace.tl();
	int w = scale * maxFace.width;//ԭͼ�еĿ��
	int h = scale * maxFace.height;//ԭͼ�еĸ߶�
	int x = scale * (p.x);//ԭͼ�е����Ͻ�
	int y = scale * (p.y);//ԭͼ�е����Ͻ�
	Rect faceLocation(x, y, w, h);
	//faceLocation &= Rect(0, 0, src.cols, src.rows);
	faceRect = faceLocation;
	//rectangle(dst, faceLocation, Scalar(0, 255, 0), 2);
	//rectangle(cover, faceLocation, Scalar(0, 0, 0), -1);//--------------------��Ĥ
	return 1;
}