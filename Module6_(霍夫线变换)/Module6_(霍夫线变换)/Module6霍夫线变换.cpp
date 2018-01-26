// Module6霍夫线变换.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;


Mat doHoughLines(Mat src)
{
	//转换为灰度图
	Mat src_gray;
	Mat edges;
	Mat dst;
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	Canny(src_gray, edges, 70, 210, 3);  //先检测出该源图的所有边缘
	cvtColor(edges, dst, CV_GRAY2BGR);   //dst应是一张多通道彩图，因为后面的代码里，我们要给它它画有颜色的线条
	
	//经典霍夫线变换，获取所有直线边缘存进vector当中
	vector<Vec2f> lines;
	HoughLines(edges, lines, 1, CV_PI / 180, 150, 0, 0);
	
	//遍历vector，并将这些线段画进dst中
	for (int i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b)); //这里的1000用于拉伸线段长度，贯穿图片比较直观，不妨改成500试试，线段会明显变短
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst, pt1, pt2, Scalar(0, 255, 0), 1, 8);
	}

	imshow("edges", edges);
	return dst;
}

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Buiding.jpg");
	imshow("src", src);

	Mat dst_hough = doHoughLines(src);
	imshow("dst_hough", dst_hough);
	
	waitKey(0);
    return 0;
}

