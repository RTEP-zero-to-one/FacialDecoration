#include "cascade.h"
CascadeClassifier cascade_face;
CascadeClassifier cascade_nose;
CascadeClassifier cascade_mouth;
CascadeClassifier cascade_eye;
void loadCascade() {
	if (!cascade_face.load(FACE_XML))
	{
		printf("face cascade filter faile!\n");
	}
	if (!cascade_nose.load(NOSE_XML))
	{
		printf("nose cascade filter faile!\n");
	}
	if (!cascade_eye.load(EYE_XML))
	{
		printf("eye cascade filter faile!\n");
	}
	if (!cascade_mouth.load(MOUTH_XML))
	{
		printf("mouth cascade filter faile!\n");
	}
}
