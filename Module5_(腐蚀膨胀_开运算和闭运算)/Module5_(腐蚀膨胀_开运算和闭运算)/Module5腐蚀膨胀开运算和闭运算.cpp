// Module5腐蚀膨胀开运算和闭运算.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"

int main(int argc, char* argv[])
{
	IplImage *origin = cvLoadImage("F:\\AppleSeed.jpg");
	IplImage *out = cvCreateImage(cvGetSize(origin),origin->depth,origin->nChannels);
	cvRepeat(origin, out);
	cvNamedWindow("Origin", CV_WINDOW_AUTOSIZE);
	cvShowImage("Origin", origin);
	
	//（1）开运算：先腐蚀再膨胀
	//效果：去除小的明亮点，剩余的明亮点被隔绝，但大小不变！
	cvErode(origin, origin, 0, 1);
	cvDilate(origin, origin, 0, 1);
	
	cvNamedWindow("Open Loop Calculate:", CV_WINDOW_AUTOSIZE);
	cvShowImage("Open Loop Calculate:", origin);

	//（2）闭运算：先膨胀后腐蚀
	//效果：亮的区域连在一起，但它们大小基本不变！
	cvDilate(out, out, 0, 1);
	cvErode(out, out, 0, 1);
	cvNamedWindow("Closed Loop Calculate:");
	cvShowImage("Closed Loop Calculate:", out);

	//（3）形态学梯度:该知识点于第六章再次讨论，这里放出公式：gradient(origin) = dilate(origin) - erode(out);
	cvAbsDiff(origin, out, out);//根据上述公式，不难想到用膨胀后的图片、腐蚀后的图片，做差即可
	cvNamedWindow("Gradient:");
	cvShowImage("Gradient:", out);

	cvWaitKey(0);
    return 0;
}

