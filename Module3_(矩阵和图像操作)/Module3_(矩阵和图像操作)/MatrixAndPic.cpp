#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	/****创建pic图像矩阵和空矩阵img****/
	float vals[9] = { 1.5,-7.7,0.5,-0.5,-0.8661,9.6,3.9,4.4,-0.811 };
	CvMat pic;
	cvInitMatHeader(&pic, 3, 3, CV_32FC1, vals);
	CvMat *img = cvCreateMat(3, 3, CV_32FC1);
	
	cvAbs(&pic,img);  //cvAbs()函数将pic矩阵的所有的元素全部取绝对值，并全部依次写入img的矩阵中
	
	cout << "cvAbs:\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CV_MAT_ELEM(*img, float, i, j) << " ";
		}
		cout << endl;
	}

	/****新建一个固定数据的图片矩阵draw，一个空图片矩阵out****/
	float arrs[9] = { 4.7,-0.788,0.914,-1.47,-0.995,-4.3168,7.71,8.42,10.9 };
	CvMat draw;
	cvInitMatHeader(&draw, 3, 3, CV_32FC1, arrs);

	CvMat *out = cvCreateMat(3, 3, CV_32FC1);
	
	cvAbsDiff(&pic, &draw, out);  //将两个图片的矩阵所有的元素对应做差，该差的绝对值写入目标图的矩阵out
	cout << "\ncvAbsDiff:\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CV_MAT_ELEM(*out, float, i, j) << " ";
		}
		cout << endl;
	}
	/****两个矩阵的元素相加并写入****/
	cvAdd(&pic, &draw, out);
	cout << "\ncvAdd:\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CV_MAT_ELEM(*out, float, i, j) << " ";
		}
		cout << endl;
	}


	system("pause");
	return 0;
}