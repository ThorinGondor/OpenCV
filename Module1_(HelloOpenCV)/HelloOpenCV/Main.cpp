#include "highgui.h"
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char* argv[])
{
	// ����һ��ͼƬ����Ϸԭ����
	Mat img = imread("F:\\Ferrari.jpg");
	// ����һ����Ϊ "��Ϸԭ��"����
	namedWindow("��Ϸԭ��");
	// �ڴ�������ʾ��Ϸԭ��
	imshow("��Ϸԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�
	waitKey(10000);
}