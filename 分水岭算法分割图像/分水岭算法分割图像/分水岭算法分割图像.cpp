// 分水岭算法分割图像.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "opencv2/video/tracking.hpp"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;


int main(int agrc[], char* argv)
{
	/*
	基本步骤：

	(1)标记背景区域；
	(2)标记前景和未知区域；
	(3)合并标记图像；
	(4)分水岭算法进行分割。*/

	/* * * * （1）标记背景区域： Mat imgbg * * * */
	Mat src = imread("F:\\OpenCVImage\\blackwhite.jpg");
	Mat frame;
	imshow("src", src);
	cvtColor(src, frame, CV_BGR2GRAY);  //灰度化
	Mat marker = frame.clone();
	
	//阈值分割（OTSU）
	threshold(marker, frame, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);    
	imshow("Otsu阈值分割图", frame);

	//去除噪声,开运算
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(frame, frame, MORPH_OPEN, element, Point(-1, -1), 2);
	
	//膨胀得到背景区域imgbg
	Mat imgbg;
	dilate(frame, imgbg, element, Point(-1, -1), 3);
	imshow("背景区域", imgbg);
	
	/* * * * （2）找前景：imageThin * * * */
	Mat imageThin(frame.size(), CV_32FC1); //定义保存距离变换结果的Mat矩阵  
	distanceTransform(frame, imageThin, CV_DIST_L2, 5);  //距离变换 
	normalize(imageThin, imageThin, 0, 255, CV_MINMAX);  //归一化利于显示
	threshold(imageThin, imageThin, 200, 255, CV_THRESH_BINARY);
	imshow("前景图", imageThin);

	/* * * * （2）找未知区域：imageThin * * * */
	//找未知区域
	imageThin.convertTo(imageThin, imgbg.type());
	Mat unknown;
	subtract(imgbg, imageThin, unknown); //图像相减
	imshow("未知区域", unknown);

	/* * * * （3）合并标记图像：imagelabel * * * */
	Mat imglabels, imgstats, imgcentroid;
	connectedComponentsWithStats(imageThin, imglabels, imgstats, imgcentroid);  //连通域标记

	imglabels = imglabels + 100;    //背景区域像素为100

	imglabels.convertTo(imglabels, CV_8U);
	for (int i = 0; i<unknown.rows; i++)
	{
		uchar* ptr = unknown.ptr<uchar>(i);
		for (int j = 0; j<unknown.cols; j++)
		{
			if (255 == ptr[j])
			{
				imglabels.at<uchar>(i, j) = 0; //未知区域像素为0
			}
		}
	}
	imshow("标记图像", imglabels);
	imglabels.convertTo(imglabels, CV_32S); //图像类型转换
	
	/* * * * （4）合并标记图像：imagelabel * * * */
	watershed(src, imglabels);
	
	imglabels.convertTo(imglabels, CV_8U);
	imshow("分水岭效果图", imglabels);


	waitKey(0);
    return 0;
}

