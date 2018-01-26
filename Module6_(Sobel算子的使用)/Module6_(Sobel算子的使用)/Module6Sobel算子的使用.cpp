// Module6Sobel算子的使用.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "highgui.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\AppleSeed.jpg");
	Mat src_gray;
	Mat grad_x;
	Mat grad_y;
	Mat dst;
	//源图转为灰度图
	cvtColor(src, src_gray, CV_BGR2GRAY);
	
	//对灰度图降噪
	blur(src_gray, src_gray, Size(3, 3));
	
	//对灰度图使用sobel算子
	Sobel(src_gray, grad_x, CV_16S, 1, 0, 3);
	convertScaleAbs(grad_x, grad_x);
	Sobel(src_gray, grad_y, CV_16S, 0, 1, 3);
	convertScaleAbs(grad_y, grad_y);
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);

	//显示最终效果
	imshow("src_gray", src_gray);
	imshow("dst", dst);
	waitKey(0);
    return 0;
}

