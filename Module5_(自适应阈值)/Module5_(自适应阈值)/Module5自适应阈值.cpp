// Module5自适应阈值.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"

IplImage *origin = cvLoadImage("F:\\AppleSeed.jpg");
IplImage *r = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
IplImage *g = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
IplImage *b = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);
IplImage *out = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 1);

void SplitImage(IplImage *origin)
{
	//制作一张灰度图
	cvSplit(origin, r, g, b, NULL);
}

void cvThreshold(IplImage *r)
{
	//对制作出来的灰度图进行自适应阈值操作：
	cvAdaptiveThreshold(r, out, 220, 0, CV_THRESH_BINARY, 9, 5);  //倒数第二个参数的设置很重要，即block_size，计算像素点周边的bxb区域并加权平均，根据图像对比度的不同该数值应做调整
}

void Show(IplImage *out)
{
	cvNamedWindow("origin", 0);
	cvShowImage("origin", origin);
	cvNamedWindow("out", 0);
	cvShowImage("out", out);
}

int main(int argc, char* agrv[])
{
	SplitImage(origin);
	cvThreshold(r);
	Show(out);
	cvWaitKey(0);
    return 0;
}

