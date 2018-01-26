// Module6累计概率霍夫变换练习.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

Mat doHoughLinesP(Mat src)
{
	Mat src_gray;
	Mat edges;
	Mat dst;
	Mat ept(800, 1200, CV_8UC3, Scalar::all(0));
	//转为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	//高斯降噪
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//canny边缘检测，获取所有轮廓线
	Canny(src_gray, edges, 30, 120, 3, false);
	//dst应为彩图
	cvtColor(edges, dst, CV_GRAY2RGB, 0);
	//累计概率霍夫变换
	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180, 150, 50, 10);
	//遍历绘制向量
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i vs = lines[i];
		line(dst, Point(vs[0], vs[1]), Point(vs[2], vs[3]), Scalar(0, 255, 0), 1, 8, 0);
		line(ept, Point(vs[0], vs[1]), Point(vs[2], vs[3]), Scalar(0, 255, 0), 1, 8, 0);
	}
	imshow("empty", ept);
	return dst;
}

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Building.jpg");
	Mat dst = doHoughLinesP(src);
	
	imshow("src", src);
	imshow("dst_hough", dst);
	waitKey(0);
    return 0;
}

