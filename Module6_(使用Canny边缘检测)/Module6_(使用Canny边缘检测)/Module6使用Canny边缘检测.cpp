// Module6使用Canny边缘检测.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Fruit.jpg");
	Mat src_gray;
	Mat edges;
	Mat dst;

	//src转换为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);

	//灰度图降噪
	blur(src_gray, src_gray, Size(3,3));

	//canny算子边缘检测
	Canny(src_gray, edges, 3, 9, 3, false);

	src.copyTo(dst, edges);
	//展示
	imshow("src", src);
	imshow("src_gray", src_gray);
	imshow("edges", edges);
	imshow("dst", dst);

	waitKey(0);
    return 0;
}

