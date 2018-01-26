// Module7寻找物体的凸包.cpp: 定义控制台应用程序的入口点。
//关键：通过轮廓来寻找物体的凸包

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;


int main()
{
	Mat src = imread("F:\\Star.jpg");
	imshow("src", src);
	Mat src_gray;
	Mat edges;

	//转为灰度图，高斯模糊，转变为二值图
	cvtColor(src, src_gray, CV_RGB2GRAY);
	GaussianBlur(src_gray, src_gray, Size(5, 5), 0, 0, BORDER_DEFAULT);
	threshold(src_gray, edges, 80, 255, CV_THRESH_BINARY);
	imshow("edges", edges);

	//寻找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//遍历轮廓，寻找凸包
	vector<vector<Point>> hull(contours.size());  //释义：hull，外壳，此指凸包
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}
	
	//绘制凸包
	Mat dst = Mat::zeros(src.size(), CV_8UC3);

	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(dst, hull, i, Scalar(0, 255, 0), 1, 8, vector<Vec4i>(), 0, Point());
	}
	imshow("dst", dst);

	waitKey(0);
    return 0;
}

