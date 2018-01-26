// Module6综合实例边缘检测.cpp: 定义控制台应用程序的入口点。
//使用canny算子，sharr滤波器，laplacian算子，sobel算子
//顺便用到高斯降噪：GaussianBlur，转换为灰度图：cvtColor，取绝对值：convertScaleAbs

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;
/************全局变量************/
Mat src = imread("F:\\Fruit.jpg");

/*********一系列检测方法*********/
Mat doCanny(Mat src)
{
	Mat src_gray;
	Mat edges;
	Mat dst;
	//转换灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	//高斯降噪
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//canny检测
	Canny(src_gray, edges, 5, 15, 3, false);
	convertScaleAbs(edges, edges, 1, 0);
	//掩码拷贝
	src.copyTo(dst, edges);
	return dst;
}

Mat doSobel(Mat src)
{
	Mat src_gray;
	Mat grad_x;
	Mat grad_y;
	Mat dst;
	//灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	//降噪
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//sobel算子
	Sobel(src_gray, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, grad_x, 1, 0);
	Sobel(src_gray, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, grad_y, 1, 0);
	//合成
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);

	return dst;
}

Mat doLaplacian(Mat src)
{
	Mat src_gray;
	Mat dst;
	
	//转为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	//降噪
	GaussianBlur(src_gray, src_gray, Size(3,3), 0, 0, BORDER_DEFAULT);
	//拉普拉斯算子
	Laplacian(src_gray, dst, CV_16S, 5, 1, 0, BORDER_DEFAULT);
	Mat abs_dst;
	convertScaleAbs(dst, abs_dst);
	return abs_dst;
}

int main(int argc, char* argv[])
{
	Mat dst_canny = doCanny(src);
	imshow("canny", dst_canny);

	Mat dst_Sobel = doSobel(src);
	imshow("Sobel", dst_Sobel);

	Mat dst_Laplacian = doLaplacian(src);
	imshow("Laplacian", dst_Laplacian);

	waitKey(0);
    return 0;
}

