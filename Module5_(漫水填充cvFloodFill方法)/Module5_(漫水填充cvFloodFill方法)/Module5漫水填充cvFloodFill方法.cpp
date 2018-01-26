// Module5漫水填充cvFloodFill方法.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"

int main(int argc, char* argv[])
{
	IplImage *pic = cvLoadImage("F:\\AppleSeed.jpg");
	cvNamedWindow("Origin", CV_WINDOW_AUTOSIZE);
	cvShowImage("Origin", pic);

	//膨胀处理
	cvDilate(pic, pic, 0, 1);
	//漫水填充：cvFloodFill();
	cvFloodFill(pic, CvPoint(500, 300), CvScalar(0,0,255), CvScalar(0,0,0), CvScalar(255,255,255), NULL, 8, NULL);
	
	cvNamedWindow("FloodFill", CV_WINDOW_AUTOSIZE);
	cvShowImage("FloodFill", pic);
	cvWaitKey(0);
    return 0;
}

