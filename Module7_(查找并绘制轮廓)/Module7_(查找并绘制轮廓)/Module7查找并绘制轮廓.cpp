// Module7查找并绘制轮廓.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
	//以二值图模式载入源图
	Mat src = imread("F:\\AppleSeed.jpg",0);
	//建立dst图，并初始化
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	//源图二值化
	threshold(src, src, 130, 255, CV_THRESH_BINARY);
    
	//定义轮廓和层次结构
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//查找轮廓
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	//遍历所有的顶层轮廓，以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for ( index = 0; index>=0;index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, index, color, FILLED, 8, hierarchy);
		cout << "index" << index << endl;
	}

	//显示
	imshow("dst", dst);
	imshow("src", src);
	waitKey(0);
    return 0;
}

