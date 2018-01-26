// Module7查找绘制图像的轮廓矩.cpp: 定义控制台应用程序的入口点。
//moments();函数，contourArea();函数，arcLength();函数

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

Mat src = imread("F:\\AppleSeed.jpg");
Mat src_gray;
Mat edges;
int g_nthreshold = 100;

void onTrackbarChange(int, void*)
{
	//获取边缘
	Canny(src_gray, edges, g_nthreshold, g_nthreshold * 2, 3, false);
	
	//获取轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	//根据轮廓计算矩
	vector<Moments> mu(contours.size());
	for (int i = 0; i < mu.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	//绘制轮廓
	Mat dst = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(dst, contours, i, Scalar(0,255,0), 2, 8, hierarchy, 0, Point());
		cout << "Area: " << contourArea(contours[i], false) << "; arcLength:" << arcLength(contours[i], true) << endl;
	}
	imshow("dst", dst);
}

int main(int argc, char* argv[])
{
	
	cvtColor(src, src_gray, CV_RGB2GRAY);
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	imshow("src_gray", src_gray);
	createTrackbar("Adjust", "src_gray", &g_nthreshold, 255, onTrackbarChange);
	
	waitKey(0);
    return 0;
}

