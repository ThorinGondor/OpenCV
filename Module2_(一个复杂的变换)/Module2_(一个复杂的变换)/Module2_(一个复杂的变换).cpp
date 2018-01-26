#include "highgui.h"
#include "cv.h"

IplImage* doPyrDown(const IplImage *origin)
{
	//������ͼ
	IplImage *out = cvCreateImage(cvSize(origin->width / 2, origin->height / 2), origin->depth, origin->nChannels);
	
	//���ţ�ԭͼ->��ͼ
	cvPyrDown(origin, out);
	
	//�����µ����ź��ͼ
	return out;
}

int main(int argc, char* argv[])
{
	cvNamedWindow("Origin_Pictrue", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("First_Pictrue", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Second_Pictrue", CV_WINDOW_AUTOSIZE);
	
	IplImage *origin = cvLoadImage("F:\\Porsche.jpg");
	cvShowImage("Origin_Pictrue", origin);
	
	IplImage *out;

	out = doPyrDown(origin);
	cvShowImage("First_Pictrue", out);

	out = doPyrDown(out);
	cvShowImage("Second_Pictrue", out);
	
	cvWaitKey(0);
	cvDestroyWindow("Origin_Pictrue");
	cvDestroyWindow("First_Pictrue");
	cvDestroyWindow("Second_Pictrue");
	return 0;
}