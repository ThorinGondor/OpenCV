#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	/****����picͼ�����Ϳվ���img****/
	float vals[9] = { 1.5,-7.7,0.5,-0.5,-0.8661,9.6,3.9,4.4,-0.811 };
	CvMat pic;
	cvInitMatHeader(&pic, 3, 3, CV_32FC1, vals);
	CvMat *img = cvCreateMat(3, 3, CV_32FC1);
	
	cvAbs(&pic,img);  //cvAbs()������pic��������е�Ԫ��ȫ��ȡ����ֵ����ȫ������д��img�ľ�����
	
	cout << "cvAbs:\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CV_MAT_ELEM(*img, float, i, j) << " ";
		}
		cout << endl;
	}

	/****�½�һ���̶����ݵ�ͼƬ����draw��һ����ͼƬ����out****/
	float arrs[9] = { 4.7,-0.788,0.914,-1.47,-0.995,-4.3168,7.71,8.42,10.9 };
	CvMat draw;
	cvInitMatHeader(&draw, 3, 3, CV_32FC1, arrs);

	CvMat *out = cvCreateMat(3, 3, CV_32FC1);
	
	cvAbsDiff(&pic, &draw, out);  //������ͼƬ�ľ������е�Ԫ�ض�Ӧ����ò�ľ���ֵд��Ŀ��ͼ�ľ���out
	cout << "\ncvAbsDiff:\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CV_MAT_ELEM(*out, float, i, j) << " ";
		}
		cout << endl;
	}
	/****���������Ԫ����Ӳ�д��****/
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