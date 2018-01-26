// Module7查找绘制轮廓使用threshold创建二值图.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;

Mat src = imread("F:\\AppleSeed.jpg");
Mat src_gray;
int g_nthreshold = 100;

void onChange(int, void*)
{
	Mat buff_src_gray ;
	//threshold(src_gray, buff_src_gray, g_nthreshold,255,CV_THRESH_BINARY);
	Canny(src_gray, buff_src_gray, g_nthreshold, g_nthreshold * 3, 3, false);
	imshow("buff_src_gray", buff_src_gray);

	vector<vector<Point>> Contours;
	vector<Vec4i> hierarchy;
	findContours(buff_src_gray, Contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    
	Mat dst = Mat::zeros(src_gray.rows,src_gray.cols,CV_8UC3);
	for (int index = 0; index >=0; index = hierarchy[index][0])
	{
		Scalar color(rand()&255,rand()&255,rand()&255);
		drawContours(dst, Contours, index, color, 1, 8, hierarchy);
	}

	
	imshow("dst", dst);
}

int main(int argc, char* argv[])
{
	
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	namedWindow("src");
	imshow("src", src);
	createTrackbar("threshold", "src", &g_nthreshold, 255, onChange);

	waitKey(0);
    return 0;
}

