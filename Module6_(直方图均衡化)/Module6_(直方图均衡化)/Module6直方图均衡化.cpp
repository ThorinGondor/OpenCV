// Module6直方图均衡化.cpp: 定义控制台应用程序的入口点。
//直方图均衡化函数方法：equalizeHist()
//该方法可以对图片进行灰度变换，能增强图片的对比度，各区域之间有了明确的边界

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;

Mat do_equalizeHist(Mat src)
{
	Mat src_gray;
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	Mat dst;
	
	//主体：直方图均衡化函数方法
	equalizeHist(src_gray, dst);
	
	imshow("src_gray", src_gray);
	return dst;
}

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\FF15.jpg");
	Mat dst_equalize = do_equalizeHist(src);
	imshow("equalizeHist", dst_equalize);
	
	waitKey(0);
    return 0;
}

