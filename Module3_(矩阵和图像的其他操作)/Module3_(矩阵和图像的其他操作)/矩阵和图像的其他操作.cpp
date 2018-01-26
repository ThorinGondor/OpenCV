#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	/****（1）cvRepeat();函数方法演示********************************************************/
	IplImage *src1 = cvLoadImage("F:\\Porsche.jpg"); //载入一个三通道图像
	IplImage *dst = cvCreateImage(cvGetSize(src1), src1->depth, src1->nChannels);

	cvRepeat(src1, dst); //将图像src1复制到dst图像
	cvNamedWindow("Out_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("Out_Pictrue", dst);
	
	/****(2)cvSplit();函数方法演示***********************************************************/
	IplImage *dst0 = cvCreateImage(cvGetSize(src1), src1->depth, 1);
	IplImage *dst1 = cvCreateImage(cvGetSize(src1), src1->depth, 1);
	IplImage *dst2 = cvCreateImage(cvGetSize(src1), src1->depth, 1);

	cvSplit(src1, dst0, dst1, dst2,NULL);  //将原图进行通道分割
	
	//需注意：虽然split已经将原图按通道分割，但是如果要显示各自通道的图像，还必须做如下合并的措施，使用cvMerge();函数方法！
	IplImage *rimg = cvCreateImage(cvGetSize(src1), src1->depth, 3);
	IplImage *gimg = cvCreateImage(cvGetSize(src1), src1->depth, 3);
	IplImage *bimg = cvCreateImage(cvGetSize(src1), src1->depth, 3);
	
	cvMerge(dst0, dst1, 0, 0, rimg);
	cvMerge(dst0, 0, dst2, 0, gimg);
	cvMerge(0, dst1, dst2, 0, bimg);

	//打印输出
	cvNamedWindow("dst0", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("dst1", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("dst2", CV_WINDOW_AUTOSIZE);
	cvShowImage("dst0", rimg);
	cvShowImage("dst1", gimg);
	cvShowImage("dst2", bimg);

	/****结束*******************************************************************************/
	cvWaitKey(0);
	cvDestroyAllWindows;
	cvReleaseImage(&src1);
	cvReleaseImage(&dst);
	cvReleaseImage(&dst0);
	cvReleaseImage(&dst1);
	cvReleaseImage(&dst2);

	return 0;
}