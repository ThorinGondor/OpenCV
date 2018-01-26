// Module6累计概率霍夫变换.cpp: 定义控制台应用程序的入口点。
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
	Mat vect(800, 1200, CV_8UC3, Scalar(0, 0, 0)); 
	//转为灰度图
	cvtColor(src, src_gray, CV_RGB2GRAY, 0);
	//高斯降噪
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//canny灰度检测，获取所有边缘
	Canny(src_gray, edges, 3, 9, 3);
	//灰度图转为多通道图
	cvtColor(edges, dst, CV_GRAY2RGB);
	//霍夫变换获取向量
	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180, 80, 150, 10);
	//遍历绘制向量
	for (int i = 0; i < lines.size(); i++)
	{
		Vec4i vs = lines[i];
		//这里我分别画到两个图dst和vect，当然只需要画到dst也是ok的
		line(dst, Point(vs[0], vs[1]), Point(vs[2], vs[3]), Scalar(0, 255, 0), 1, 8);
		line(vect, Point(vs[0], vs[1]), Point(vs[2], vs[3]), Scalar(0, 255, 0), 1, 8);
	}
	imshow("vect", vect); 
	return dst;
}

int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Building.jpg");
	Mat dst_hough = doHoughLinesP(src);
	
	imshow("dst_hough", dst_hough);
	imshow("src", src);
	waitKey(0);
    return 0;
}

