#include "cascade.h"
#include "unistd.h"
CascadeClassifier cascade_face;
CascadeClassifier cascade_nose;
CascadeClassifier cascade_mouth;
CascadeClassifier cascade_eye;
void loadCascade() {
	if (!cascade_face.load(FACE_XML))
	{
		printf("Face cascade XML file load failed!\n");
	}
	if (!cascade_nose.load(NOSE_XML))
	{
        printf("Nose cascade XML file load failed!\n");
    }
	if (!cascade_eye.load(EYE_XML))
	{
        printf("Eye cascade XML file load failed!\n");
    }
	if (!cascade_mouth.load(MOUTH_XML))
	{
        printf("Mouth cascade XML file load failed!\n");
    }
}
