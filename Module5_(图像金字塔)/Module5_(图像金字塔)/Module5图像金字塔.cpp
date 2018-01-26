// Module5图像金字塔.cpp: 定义控制台应用程序的入口点。
/****
    金字塔是图像的集合，主要的金字塔有两种：
	                      |---高斯金字塔：，向下采样，因此应该用于缩小图片，方法是cvPyrDown();，cvPyrUp()则不建议采用【但是下述方法已经过时，还是只能用这个啊！】
						  |---拉普拉斯金字塔：向上采样，因此应该用于放大图片,方法是cvPyrSegmentation();该方法已经过时
****/

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"


int main(int argc, char* argv[])
{
	IplImage *origin = cvLoadImage("F:\\AppleSeed.jpg");
	IplImage *small = cvCreateImage(CvSize(origin->width / 2, origin->height / 2), origin->depth, origin->nChannels);
	IplImage *large = cvCreateImage(CvSize(origin->width * 2, origin->height * 2), origin->depth, origin->nChannels);
	
	//该cvPyrDown()函数方法隶属于：高斯金字塔，高斯金字塔属于向下降采样，且该方法属于缩小，因此无损
	cvPyrDown(origin, small, CV_GAUSSIAN_5x5);
	
	//看看下面这个函数:放大图片的cvPyrUp();同样属于高斯金字塔，但它其实不是PyrDown();的逆运算，而且它属于向上采样，会出现信息损失，建议不用
	//cvPyrUp(origin, large, CV_GAUSSIAN_5x5);

	//拉普拉斯金字塔适用于放大图片，方法是cvPyrSegmentation();
	/*CvMemStorage *storage = cvCreateMemStorage(0);
	cvPyrSegmentation(origin,large,storage,NULL,4,200,50);

	
	cvNamedWindow("PyrSegmentation", CV_WINDOW_AUTOSIZE);
	cvShowImage("PyrSegmentation", large);*/
	cvNamedWindow("PyrDown", CV_WINDOW_AUTOSIZE);
	cvShowImage("PyrDown", small);
	cvWaitKey(0);
    return 0;
}

