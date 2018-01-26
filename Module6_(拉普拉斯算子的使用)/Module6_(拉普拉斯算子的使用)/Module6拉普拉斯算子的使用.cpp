// Module6拉普拉斯算子的使用.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;


int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Ferrari.jpg");
	Mat src_gray;
	Mat dst;

	//转化为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	
	//降噪处理
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);

	//拉普拉斯算子
	Laplacian(src_gray, dst, CV_16S, 5, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, dst, 1, 0);

	//显示
	imshow("src_gray", src_gray);
	imshow("dst", dst);

	waitKey(0);
    return 0;
}

