// Module6重映射remap函数方法.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

Mat doRemap(Mat src)
{
	cout << "就是";
	
	Mat src_gray;
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	Mat map_x;
	Mat map_y;
	Mat dst;
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);
	dst.create(src.size(), src.type());

	//遍历每个像素点，改变map_X和map_y的值
	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(src.rows - j);
		}
	}
	remap(src, dst, map_x, map_y, INTER_LINEAR, 0, Scalar(0, 0, 0));
	return dst;
}

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Porsche.jpg");
	Mat dst = doRemap(src);
	imshow("dst", dst);
	waitKey(0);
    return 0;
}

