// Module3数据存储.cpp: 定义控制台应用程序的入口点。
//保存该矩阵，并读取该矩阵

//保存矩阵函数方法： cvSave();
//读取矩阵函数方法： cvLoad();

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>

int main(int argc, char* argv[])
{
	float vals[9] =
	{
		14.7,22.4,91.72,
		8.5,47.68,90.34,
		23.7,9.8,7.71
	};
	CvMat *rotmat = new CvMat;
	cvInitMatHeader
	(
		rotmat, 3, 3, CV_32FC1, vals
	);
	//保存该矩阵，并读取该矩阵
	cvSave("F:\\MatrixStorage.xml", rotmat);
	CvMat* out = (CvMat*)cvLoad("F:\\MatrixStorage.xml");
	
	std::cout.fill('-');
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout.width(6);
			std::cout << cvGetReal2D(out, i, j) << " ";
		}
		std::cout << '\n';
	}

	cvWaitKey(0);
	system("pause");
    return 0;
}

