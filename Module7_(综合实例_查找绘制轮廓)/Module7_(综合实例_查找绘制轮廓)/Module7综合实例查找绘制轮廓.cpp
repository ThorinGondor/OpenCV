// Module7综合实例查找绘制轮廓.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;
void on_threshChange(int, void*);

Mat src = imread("F:\\AppleSeed.jpg");
Mat src_gray;
int g_threshold = 100;


int main(int argc, char* argv)
{
	cvtColor(src,src_gray,CV_RGB2GRAY,0);
	GaussianBlur(src_gray, src_gray, Size(3, 3),0, 0, BORDER_DEFAULT);

	namedWindow("src");
	imshow("src", src);
	createTrackbar("canny_threshold", "src", &g_threshold, 255, on_threshChange);
	waitKey(0);
    return 0;
}

void on_threshChange(int,void*)
{
	Mat edges;
	Mat dst = Mat::zeros(src.size(), CV_8UC3);
	//Canny检测来获取图片的所有轮廓
	Canny(src_gray, edges, g_threshold, g_threshold * 3, 3, false);
	
	//构造轮廓的向量和层次结构的向量，用于存储轮廓、轮廓的层次结构
	vector<vector<Point>> Contours;  //轮廓的向量组合
	vector<Vec4i> hierarchy;     //轮廓的层次结构 <a,b,c,d>
	findContours(edges, Contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	
	//遍历contours，输出这些轮廓
	for (int index = 0; index >=0; index=hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, Contours, index, color, 1, 8, hierarchy);
	}
	
	imshow("edges", edges);
	imshow("dst", dst);
}