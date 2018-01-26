#include "highgui.h"
#include <iostream>
using namespace std;

int main(int argc,char* argv[])
{
	//£®1£©œ‘ æÕºœÒ£∫
	IplImage* img = cvLoadImage("F:\\Ferrari.jpg");
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example1", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Example1");

	//£®2£©≤•∑≈ ”∆µ£∫
	cvNamedWindow("Example2", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("F:\\pnm4.avi");
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(capture);
		cvShowImage("Example2", frame);
		char ch = cvWaitKey(33);
		if (ch == 27)
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Example2");
}