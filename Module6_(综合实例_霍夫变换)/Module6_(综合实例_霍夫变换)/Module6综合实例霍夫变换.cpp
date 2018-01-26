// Module6综合实例霍夫变换.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

/**********全局变量***********/
Mat src;
Mat src_gray;
Mat edges;

int g_nthreshold = 150;

/***********滑动条事件处理************/
void on_HoughLines(int,void*)
{
	Mat dst(800,1200,CV_8UC3,Scalar::all(0));
	cvtColor(src, src_gray,CV_RGB2GRAY, 0);
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Canny(src_gray, edges, 50, 200, 3, false);
	//cvtColor(edges, dst, CV_GRAY2RGB, 0);
	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180, g_nthreshold,50,10);

	for (int i = 0; i < lines.size(); i++)
	{
		line(dst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 255, 0), 1, 8, 0);
	}
	imshow("Final Show", dst);
}

int main(int argc, char* argv[])
{
    src = imread("F:\\Building.jpg");
	imshow("src", src);

	namedWindow("Final Show", 1);
	createTrackbar("value", "Final Show",&g_nthreshold, 200, on_HoughLines);
	


	waitKey(0);
    return 0;
}

