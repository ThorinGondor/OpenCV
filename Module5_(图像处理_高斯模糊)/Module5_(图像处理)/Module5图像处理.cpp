// Module5图像处理.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"


int main(int argc, char* argv[])
{
	cvNamedWindow("Origin", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Gussian", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("cvErode", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("cvDilate", CV_WINDOW_AUTOSIZE);
	

	IplImage *origin = cvLoadImage("F:\\Detect.jpg");cvShowImage("Origin", origin);
	IplImage *out = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, origin->nChannels);
	//高斯模糊：
	cvSmooth(origin, out, CV_GAUSSIAN, 5, 5, 5, 0);
	cvShowImage("Gussian", out);

	//膨胀和腐蚀cvDilate();和 cvErode();
	    //可以自定义核，如下代码，该行代码不写也可以，系统自动会使用默认的核
	    cvCreateStructuringElementEx(5, 5, 3, 3, CV_SHAPE_ELLIPSE, NULL);
	
	cvErode(origin, out, 0, 1);
	cvShowImage("cvErode", out);

	cvDilate(origin, out, 0, 1);
	cvShowImage("cvDilate", out);

	
	cvWaitKey(0);
    return 0;
}

