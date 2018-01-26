#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* agrv[])
{
	/****（1）用固定数据创建一个矩阵****/
	//建立数组,建立CvMat矩阵
	float values[6] = { 0.866025,-0.500000,0.500000,0.866025,0.377425,-0.377425 };
	CvMat rotmat;
	//通过 cvInitMatHeader(); 方法来将数组的内容存入矩阵当中
	cvInitMatHeader(&rotmat,2,3,CV_32FC1,values);
	
	/****（2）矩阵数据的读取****/
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CV_MAT_ELEM(rotmat, float, i, j) << " ";
		}
		cout << endl;
	}

	/****（3）矩阵数据的设置****/
	float num = 7.7;
	*((float*)CV_MAT_ELEM_PTR(rotmat, 0, 0)) = num;
	cout << "After The Rect:\n";
	cout << CV_MAT_ELEM(rotmat, float, 0, 0) << endl;

	cvWaitKey(0);
	system("pause");
	return 0;
}