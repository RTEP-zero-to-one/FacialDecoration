

#include "cascade.h"
CascadeClassifier cascade_face;
CascadeClassifier cascade_nose;
CascadeClassifier cascade_mouth;
CascadeClassifier cascade_eye;
void loadCascade() {
	if (!cascade_face.load(FACE_XML))
	{
		printf("�����������������󣬿���δ�ҵ��ļ����������ļ�������Ŀ¼�£�\n");
	}
	if (!cascade_nose.load(NOSE_XML))
	{
		printf("���Ӽ������������󣬿���δ�ҵ��ļ����������ļ�������Ŀ¼�£�\n");
	}
	if (!cascade_eye.load(EYE_XML))
	{
		printf("�۾��������������󣬿���δ�ҵ��ļ����������ļ�������Ŀ¼�£�\n");
	}
	if (!cascade_mouth.load(MOUTH_XML))
	{
		printf("��ͼ������������󣬿���δ�ҵ��ļ����������ļ�������Ŀ¼�£�\n");
	}
}