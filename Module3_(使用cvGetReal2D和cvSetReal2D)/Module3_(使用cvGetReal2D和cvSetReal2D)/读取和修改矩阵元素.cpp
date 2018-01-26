#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	/****��1������ͼƬ���ص���ֵһ�ֱȽϼ򵥵ķ���������ͼ�������е�������ֵ****/
	IplImage *pic = cvLoadImage("F:\\Tencent.jpg");

	/*
	//�������ͼƬ���������ص���ֵ
	for (int i = 0; i < pic->height; i++)
	{
		for (int j = 0; j < pic->width; j++)
		{
			cout << CV_IMAGE_ELEM(pic, float, i, j);
		}
	}
	cout << "System end!\n" << endl;
	*/

	/****��2������ͼƬ���ص���ֵһ�ֱȽϸ��ӵķ���****/
	//����ͼƬ���󣬰������Ԫ�ش������
	float vals[9] = { 4.1,5.9,-0.5,7.7,0.81,1.4,-0.34,5.9,7.1 };
	CvMat arr;

	cvInitMatHeader(&arr, 3, 3, CV_32FC1, vals);
	//���ʾ�������Ԫ��
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

	/****��3������ͼƬ��������ص���ֵ****/
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