#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	/****（1）访问图片像素的数值一种比较简单的方法，遍历图像中所有的像素数值****/
	IplImage *pic = cvLoadImage("F:\\Tencent.jpg");

	/*
	//遍历输出图片的所有像素的数值
	for (int i = 0; i < pic->height; i++)
	{
		for (int j = 0; j < pic->width; j++)
		{
			cout << CV_IMAGE_ELEM(pic, float, i, j);
		}
	}
	cout << "System end!\n" << endl;
	*/

	/****（2）访问图片像素的数值一种比较复杂的方法****/
	//创建图片矩阵，把数组的元素存入矩阵
	float vals[9] = { 4.1,5.9,-0.5,7.7,0.81,1.4,-0.34,5.9,7.1 };
	CvMat arr;

	cvInitMatHeader(&arr, 3, 3, CV_32FC1, vals);
	//访问矩阵所有元素
	cout << "Method: cvGetReal2D();" << endl;
	for (int i = 0; i < arr.width; i++)
	{
		for (int j = 0; j < arr.height; j++)
		{
			cout << cvGetReal2D(&arr, i, j) << " ";
		}
		cout << endl;
	}
	cout << "\nMethod: cvGet2D();" << endl;
	for (int i = 0; i < arr.width; i++)
	{
		for (int j = 0; j < arr.height; j++)
		{
			cout << cvGet2D(&arr,i,j).val << " ";
		}
		cout << endl;
	}

	/****（3）设置图片矩阵的像素的数值****/
	for (int i = 0; i < arr.height; i++)
	{
		for (int j = 0; j < arr.width; j++)
		{
			cvSetReal2D(&arr, i, j, 10);
		}
	}
	cout << "\nAfter The cvSetReal2D(); " << endl;
	for (int i = 0; i < arr.width; i++)
	{
		for (int j = 0; j < arr.height; j++)
		{
			cout << cvGetReal2D(&arr, i, j) << " ";
		}
		cout << endl;
	}
	
	cvWaitKey(0);
	system("pause");
	return 0;
}