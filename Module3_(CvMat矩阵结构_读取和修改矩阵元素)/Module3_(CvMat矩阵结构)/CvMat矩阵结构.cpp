#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* agrv[])
{
	/****��1���ù̶����ݴ���һ������****/
	//��������,����CvMat����
	float values[6] = { 0.866025,-0.500000,0.500000,0.866025,0.377425,-0.377425 };
	CvMat rotmat;
	//ͨ�� cvInitMatHeader(); ����������������ݴ��������
	cvInitMatHeader(&rotmat,2,3,CV_32FC1,values);
	
	/****��2���������ݵĶ�ȡ****/
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CV_MAT_ELEM(rotmat, float, i, j) << " ";
		}
		cout << endl;
	}

	/****��3���������ݵ�����****/
	float num = 7.7;
	*((float*)CV_MAT_ELEM_PTR(rotmat, 0, 0)) = num;
	cout << "After The Rect:\n";
	cout << CV_MAT_ELEM(rotmat, float, 0, 0) << endl;

	cvWaitKey(0);
	system("pause");
	return 0;
}