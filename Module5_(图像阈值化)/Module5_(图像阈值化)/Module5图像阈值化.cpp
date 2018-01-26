// Module5图像阈值化.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"

//载入、创建图片，都是全局变量
IplImage *origin = cvLoadImage("F:\\AppleSeed.jpg");
IplImage *R = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
IplImage *G = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
IplImage *B = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);

void SplitPic(IplImage *origin)
{
	cvSplit(origin, R, G, B, NULL);
}

int main(int argc, char* argv[])
{
	//制作单通道图片
	SplitPic(origin);

	IplImage *out1 = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
	IplImage *out2 = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
	IplImage *out3 = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
	IplImage *out4 = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
	IplImage *out5 = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
	
	//一系列不同的阈值化方法:
	cvThreshold(R, out1, 170, 255, CV_THRESH_BINARY); //图像阈值化，源图必须是张：单通道灰度图，目标图也是一张灰度图，且数据格式和源图相同！
	cvThreshold(R, out2, 170, 255, CV_THRESH_BINARY_INV); 
	cvThreshold(R, out3, 100, 100, CV_THRESH_TRUNC);
	cvThreshold(R, out4, 100, 255, CV_THRESH_TOZERO);
	cvThreshold(R, out5, 100, 255, CV_THRESH_TOZERO_INV);

	//打印显示
	cvNamedWindow("out1", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("out2", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("out3", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("out4", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("out5", CV_WINDOW_AUTOSIZE);

	cvShowImage("out1", out1);
	cvShowImage("out2", out2);
	cvShowImage("out3", out3);
	cvShowImage("out4", out4);
	cvShowImage("out5", out5);

	cvWaitKey(0);
    return 0;
}

