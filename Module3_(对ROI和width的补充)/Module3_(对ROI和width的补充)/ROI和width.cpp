#include "highgui.h"
#include "cv.h"

int main(int argc,char* argv[])
{
	//����һ��ͼ������
	IplImage *origin = cvLoadImage("F:\\Porsche.jpg");
	assert(origin->width % 2 == 0 && origin->height % 2 == 0);
	IplImage *pic = cvCreateImage(cvSize(origin->width / 2, origin->height / 2), origin->depth, origin->nChannels);
	cvPyrDown(origin, pic);

	//����ROI������÷�����cvSetImageROI();
	int x = 50;
	int y = 50;
	int width = 200;
	int height = 200;
	int add = 100;
	cvSetImageROI(pic,cvRect(x,y,width,height));//���ø���Ȥ����
	cvAddS(pic, cvScalar(add), pic);  //��������������cvAddS();�������scalar��RGB��ֵʱ�������ڸ�������,����������Ӱ��

	//������ɺ�Ҫȡ��ROI������÷�����cvResetImageROI();
	cvResetImageROI(pic);
	//��ӡ���
	cvNamedWindow("Out_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("Out_Pictrue", pic);

	cvWaitKey(0);
	return 0;
}