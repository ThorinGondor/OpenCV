#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	/****��1��cvRepeat();����������ʾ********************************************************/
	IplImage *src1 = cvLoadImage("F:\\Porsche.jpg"); //����һ����ͨ��ͼ��
	IplImage *dst = cvCreateImage(cvGetSize(src1), src1->depth, src1->nChannels);

	cvRepeat(src1, dst); //��ͼ��src1���Ƶ�dstͼ��
	cvNamedWindow("Out_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("Out_Pictrue", dst);
	
	/****(2)cvSplit();����������ʾ***********************************************************/
	IplImage *dst0 = cvCreateImage(cvGetSize(src1), src1->depth, 1);
	IplImage *dst1 = cvCreateImage(cvGetSize(src1), src1->depth, 1);
	IplImage *dst2 = cvCreateImage(cvGetSize(src1), src1->depth, 1);

	cvSplit(src1, dst0, dst1, dst2,NULL);  //��ԭͼ����ͨ���ָ�
	
	//��ע�⣺��Ȼsplit�Ѿ���ԭͼ��ͨ���ָ�������Ҫ��ʾ����ͨ����ͼ�񣬻����������ºϲ��Ĵ�ʩ��ʹ��cvMerge();����������
	IplImage *rimg = cvCreateImage(cvGetSize(src1), src1->depth, 3);
	IplImage *gimg = cvCreateImage(cvGetSize(src1), src1->depth, 3);
	IplImage *bimg = cvCreateImage(cvGetSize(src1), src1->depth, 3);
	
	cvMerge(dst0, dst1, 0, 0, rimg);
	cvMerge(dst0, 0, dst2, 0, gimg);
	cvMerge(0, dst1, dst2, 0, bimg);

	//��ӡ���
	cvNamedWindow("dst0", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("dst1", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("dst2", CV_WINDOW_AUTOSIZE);
	cvShowImage("dst0", rimg);
	cvShowImage("dst1", gimg);
	cvShowImage("dst2", bimg);

	/****����*******************************************************************************/
	cvWaitKey(0);
	cvDestroyAllWindows;
	cvReleaseImage(&src1);
	cvReleaseImage(&dst);
	cvReleaseImage(&dst0);
	cvReleaseImage(&dst1);
	cvReleaseImage(&dst2);

	return 0;
}