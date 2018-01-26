#include "highgui.h"
#include "cv.h"

int main(int argc, char* argv[])
{
	//��������ԭͼ������ֻ��Ҫ������ͼ���Եĸ���Ȥ��������ںϣ����������������������Ȥ����
	IplImage *src1 = cvLoadImage("F:\\watchdog1.jpg");
	IplImage *src2 = cvLoadImage("F:\\watchdog2.jpg");
	cvSetImageROI(src1, CvRect(150, 200, 500, 500));
	cvSetImageROI(src2, CvRect(800, 180, 500, 500));

	//ͼƬ�ںϣ�ֻ������������Ȥ�����ںϣ��ں����Ժ�ȡ��src1�ĸ���Ȥ��������src1��ͼƬ��������һ�׶�ȫ����ʾ��
	double alpha = 0.4;
	double beta = 0.6;
	cvAddWeighted(src1, alpha, src2, beta, 0, src1);
	cvResetImageROI(src1);

	//��ӡ���
	cvNamedWindow("out_pictrue",CV_WINDOW_AUTOSIZE);
	cvShowImage("out_pictrue", src1);
	cvWaitKey(0);

	cvDestroyWindow("out_pictrue");
	cvReleaseImage(&src1);
	cvReleaseImage(&src2);
	return 0;
}