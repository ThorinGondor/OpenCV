#include "highgui.h"
#include "cv.h"

int main(int argc, char*argv[])
{
	//载入一张原图，并展示
	IplImage *origin = cvLoadImage("F:\\Porsche.jpg");
	cvNamedWindow("Origin_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("Origin_Pictrue", origin);
	//创建一张空图，尺寸与原图相同
	IplImage *out = cvCreateImage(cvGetSize(origin), IPL_DEPTH_8U, 3);
	//使用高斯平滑处理
	cvSmooth(origin, out, CV_GAUSSIAN_5x5, 3, 3);
	//展示新平滑处理以后的图
	cvNamedWindow("New_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("New_Pictrue",out);
	//等待
	cvWaitKey(0);
	return 0;
}