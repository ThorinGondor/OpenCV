// Module7分水岭算法watershed函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

Mat src = imread("F:\\Quadrotor.jpg");
Mat mask = Mat::zeros(src.size(),CV_8UC1);
Mat mask2(mask.size(), CV_8UC3);



Point previous_Point(-1,-1);

static void onMouse(int event, int x, int y, int flag, void*)  //在源图src和mask同时上绘制白线（完全相同）
{
	if (x<0 || x>src.cols || y<0 || y>src.rows)
		return;
	else if (event == EVENT_LBUTTONUP || !(flag&EVENT_FLAG_LBUTTON))
		previous_Point = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		previous_Point = Point(x, y);
	else if (event == EVENT_MOUSEMOVE && (flag&EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previous_Point.x < 0)
			previous_Point = pt;
		line(mask, previous_Point, pt, Scalar(255, 255, 255), 5, 8, 0);
		line(src, previous_Point, pt, Scalar(255, 255, 255), 5, 8, 0);
		previous_Point = pt;
		imshow("MouseEvent", src);
	}
}

int main(int argc, char* argv[])
{
	cvtColor(src, mask, CV_RGB2GRAY);
	mask2 = Scalar::all(0);
	imshow("MouseEvent", src);
	setMouseCallback("MouseEvent",onMouse);

	while (1)
	{
		//绘制完白线，敲击‘1’按键继续，对mask2图进行轮廓获取和绘制
		int c = waitKey(0);
		if ((char)c == '1' || (char)c == ' ')
		{
			int compCount = 0;
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			findContours(mask, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE);
			for (int index = 0; index>=0;index = hierarchy[index][0],compCount++)
		    {
				drawContours(mask2, contours, index, Scalar::all(compCount+1), 1, 8, hierarchy, INT_MAX);
		    }
			imshow("mask2", mask2);

			vector<Vec3b> colorTab;
			for (int i = 0; i < compCount; i++)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);
				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}

			watershed(src, mask2);
			Mat watershed_img(src.size(), CV_8UC3);
			for (int i = 0; i < mask2.rows; i++)
			{
				for (int j = 0; j < mask2.cols; j++)
				{
					int index = mask2.at<int>(i, j);
					if (index == -1)
						watershed_img.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
					else if (index <= 0)
						watershed_img.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
					else
						watershed_img.at<Vec3b>(i, j) = colorTab[index - 1];
				}
			}
			imshow("mask2", mask2);
		}
		
	}

	waitKey(0);
    return 0;
}

