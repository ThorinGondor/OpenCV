#include "highgui.h"
#include "cv.h"

int main(int argc, char*argv[])
{
	//����һ��ԭͼ����չʾ
	IplImage *origin = cvLoadImage("F:\\Porsche.jpg");
	cvNamedWindow("Origin_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("Origin_Pictrue", origin);
	//����һ�ſ�ͼ���ߴ���ԭͼ��ͬ
	IplImage *out = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 3);
	//ʹ�ø�˹ƽ������
	cvSmooth(origin, out, CV_GAUSSIAN_5x5, 3, 3);
	//չʾ��ƽ�������Ժ��ͼ
	cvNamedWindow("New_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("New_Pictrue",out);
	//�ȴ�
	cvWaitKey(0);
	return 0;
}