// Module6卷积Sobel算子.cpp: 定义控制台应用程序的入口点。
/*****
第一步：开辟两个和原始图像一样大小的图像内存区，只是
其深度为IPL_DEPTH_16S,假设原始图像为pSrc(iplimage结构)
   IplImage *p16SX = cvCreateImage(cvSize(pSrc->width,pSrc->height),IPL_DEPTH_16S,1);
   IplImage *p16SY = cvCreateImage(cvSize(pSrc->width,pSrc->height),IPL_DEPTH_16S,1);
   p16SX->origin = pSrc->origin;
   p16SY->origin = pSrc->origin;

第二步：调用cvSobel进行边缘计算
   cvSobel(pSrc,p16SX,1,0,3);//x方向的边缘
   cvSobel(pSrc,p16SY,0,1,3);//y方向的边缘

第三步：计算sqrt(x^2+y^2)，得到幅值图像
   cvMul(p16SX,p16SX,p16SX,1.0);
   cvMul(p16SY,p16SY,p16SY,1.0);
   cvAdd(p16SX,p16SY,p16SX,0);

最后一步：将16S图像转化成8bit图像
   cvConvert(p16SX,pDst);
*****/

#include "stdafx.h"
#include "highgui.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main(int argc, char* argv[])
{
	//（0）创建一个单通道的DEPTH_8U的图
	IplImage *zero = cvLoadImage("F:\\watchdog2.jpg");
	IplImage *src0 = cvCreateImage(cvGetSize(zero), IPL_DEPTH_8U, 1);
	IplImage *src1 = cvCreateImage(cvGetSize(zero), IPL_DEPTH_8U, 1);
	IplImage *src2 = cvCreateImage(cvGetSize(zero), IPL_DEPTH_8U, 1);
	cvSplit(zero, src0, src1, src2, NULL);
	
	//（1）开辟两个DEPTH_16S的图像，origin应对齐！此处易忘！！！
	IplImage *picX = cvCreateImage(cvGetSize(src0), IPL_DEPTH_16S, 1);
	IplImage *picY = cvCreateImage(cvGetSize(src0), IPL_DEPTH_16S, 1);
	picX->origin = src0->origin;
	picY->origin = src0->origin;

	//（2）调用cvSobel进行边缘计算，一个图用于x方向求导，一个图用于y方向求导
	cvSobel(src0, picX, 1, 0, 1);
	cvSobel(src0, picY, 0, 1, 1);

	//（3）计算sqrt(x^2+y^2)，得到幅值图像
	cvMul(picX, picX, picX, 1);
	cvMul(picY, picY, picY, 1);
	cvAdd(picX, picY, picX, 0);
	
	//打印显示
	cvNamedWindow("cvSobel", 0);
	cvShowImage("cvSobel", picX);

	//至此，sobel处理结束，下面是进一步的二值阈值化
	/************************************************************************/
	IplImage *dst = cvCreateImage(cvGetSize(picX), IPL_DEPTH_8U, 1);
	cvConvert(picX, dst);

	cvThreshold(dst, dst, 250, 255, CV_THRESH_BINARY_INV);
	
	cvNamedWindow("cvThreshold", CV_WINDOW_AUTOSIZE);
	cvShowImage("cvThreshold", dst);
	cvWaitKey(0);
    return 0;
}

