// Module7寻找凸包练习.cpp: 定义控制台应用程序的入口点。
//凸包（Hull）和轮廓（contours）的数据类型相同，都是vector<vector<Point>>，但是凸包并没有hierarchy层次结构，轮廓则有

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

Mat src = imread("F:\\Ferrari.jpg");
Mat src_gray;
int g_nthresh = 100;

vector<vector<Point>> contours;
vector<Vec4i> hierarchy;

void onTrackbarChange(int, void*)
{
	Mat edges;
	//使用阈值进行二值化
	threshold(src_gray, edges, g_nthresh, 255, CV_THRESH_BINARY);
	imshow("edges", edges);
	
	//寻找轮廓,将轮廓的各个向量存入vector容器中
	findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	
	/****本例代码的重点，函数方法：convexHull();****/
	//遍历轮廓寻找凸包,将找到的凸包的各个向量存入vector容器中
	vector<vector<Point>> Hull(contours.size());
	for (int i = 0; i < Hull.size(); i++)
	{
		convexHull(contours[i], Hull[i]);
	}
	
	//遍历绘制凸包的轮廓，便于直观显示
	Mat dst = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i < Hull.size(); i++)
	{
		drawContours(dst, Hull, i, Scalar(0, 255, 0), 1, 8, vector<Vec4i>(), 0, Point());
	}
	imshow("dst", dst);
	
}

int main(int argc, char* argv[])
{	
	//转为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY);
	//模糊降噪
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	namedWindow("src_gray", 0);
	imshow("src_gray", src_gray);

	//滚动条，召唤滚动函数
	createTrackbar("Adjust Threshold", "src_gray", &g_nthresh, 255, onTrackbarChange);

	waitKey(0);
    return 0;
}

