// Module6仿射变换.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
	Mat src = imread("F:\\Porsche.jpg");
	Mat dst(src.rows, src.cols, src.type());
	Mat dst2(src.rows, src.cols, src.type());
	Mat warpSample(2, 3, CV_32FC1);  //变换样本
	Mat rotatSample(2, 3, CV_32FC1);

	/***************************************************************************/
	//获取变换样本：即，将该变换样本赋给warpSample图
	Point2f src_triangle[3];
	Point2f dst_triangle[3];

	src_triangle[0] = Point2f(0, 0);
	src_triangle[1] = Point2f((float)(src.cols - 1), 0);
	src_triangle[2] = Point2f(0, (float)(src.rows - 1));

	dst_triangle[0] = Point2f(0, (float)(src.rows*0.33));
	dst_triangle[1] = Point2f((float)(src.cols*0.35), 0);
	dst_triangle[2] = Point2f((float)(src.cols*0.15), (float)(src.rows*0.6));

	warpSample = getAffineTransform(src_triangle, dst_triangle);
	/***************************************************************************/
	
	//仿射变换，本例代码的主体:
	warpAffine(src, dst, warpSample, Size(src.rows, src.cols), INTER_LINEAR, BORDER_CONSTANT, Scalar(0));

	

	/****************************************************************************/
	//获取缩放样本：即，将该缩放样本赋给rotatSample
	rotatSample = getRotationMatrix2D(Point2f(src.rows / 2, src.cols / 2), 40, 0.5);
	/****************************************************************************/
	
	//仿射变换，本例代码的主体:
	warpAffine(dst, dst2, rotatSample, dst.size(), 1);
	
	imshow("dst", dst);
	imshow("dst2", dst2);
	waitKey(0);
    return 0;
}

