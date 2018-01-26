// Module6Scharr滤波器的使用.cpp: 定义控制台应用程序的入口点。
/****
    Scharr()；函数方法，该滤波器的参数和Sobel算子的参数很像，只是没有Sobel的自定义核kennel（例如3x3的核）
****/

#include "stdafx.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Watson.jpg");
	Mat src_gray;
	Mat grad_x;
	Mat grad_y;
	Mat dst;
	imshow("src", src);
	
	//转化为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	
	//高斯降噪
	GaussianBlur(src_gray, src_gray, Size(5, 5), 0, 0, BORDER_DEFAULT);
	
	//scharr滤波器
	Scharr(src_gray, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, grad_x, 1, 0);//勿忘，取绝对值！
	Scharr(src_gray, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, grad_y, 1, 0);
	
	//合并x梯度的图、y梯度的图
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);
	
	//显示
	imshow("dst",dst);
	waitKey(0);
    return 0;
}