// Module6霍夫圆变换.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

Mat doHoughCircle(Mat src)
{
	Mat src_gray;
	Mat edges;
	Mat dst;
	//转为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	//降噪
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//canny边缘检测
	Canny(src_gray, edges, 50, 200, 3, false);
	imshow("edges", edges);
	//dst为多通道
	cvtColor(edges, dst, CV_GRAY2RGB, 0);
	//霍夫圆变换
	vector<Vec3f> lines;
	HoughCircles(edges, lines, HOUGH_GRADIENT, 1, 10, 100, 100, 0, 0);
	//遍历绘制
	for (int i = 0; i < lines.size(); i++)
	{
		circle(dst,Point(lines[i][0],lines[i][1]), lines[i][2], Scalar(0, 0, 255), 1, 8, 0);
	}
	return dst;
}

int main(int argc, char* argv)
{
	Mat src = imread("F:\\circle.jpg");
	imshow("src", src);
	Mat dst_hough = doHoughCircle(src);
	imshow("HoughCircle", dst_hough);
	waitKey(0);
	return 0;
}

