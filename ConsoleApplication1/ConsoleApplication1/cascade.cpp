

#include "cascade.h"
CascadeClassifier cascade_face;
CascadeClassifier cascade_nose;
CascadeClassifier cascade_mouth;
CascadeClassifier cascade_eye;
void loadCascade() {
	if (!cascade_face.load(FACE_XML))
	{
		printf("脸部级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！\n");
	}
	if (!cascade_nose.load(NOSE_XML))
	{
		printf("鼻子级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！\n");
	}
	if (!cascade_eye.load(EYE_XML))
	{
		printf("眼睛级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！\n");
	}
	if (!cascade_mouth.load(MOUTH_XML))
	{
		printf("嘴巴级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！\n");
	}
}