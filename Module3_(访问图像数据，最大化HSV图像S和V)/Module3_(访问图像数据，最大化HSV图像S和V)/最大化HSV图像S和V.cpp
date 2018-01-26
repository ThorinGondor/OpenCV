#include "highgui.h"
#include "cv.h"

//�ı�һ��ͼ��H��S��V����ı��ͼ�����ȡ����Ͷȵ�
IplImage* saturate_SV(IplImage *pic)
{
	IplImage *buff = pic;
	for (int y = 0; y < buff->height; y++)
	{
		uchar* ptr = (uchar*)(buff->imageData + y*buff->widthStep);  //����ÿһ��
		for (int x = 0; x < buff->width; x++)  //����ÿһ�У�ÿһ�еĸ���Ԫ�أ�
		{
			ptr[3 * x] = ptr[3*x]+10;
			ptr[3 * x + 1] = ptr[3 * x + 1]+10;
			ptr[3 * x + 2] = ptr[3 * x + 2]+10;
		}
	}
	return buff;
}

int main(int agrc, char* argv[])
{
	//����ԭͼpic
	IplImage *pic = cvLoadImage("F:\\DeepSea.jpg");
	//����imgͼ������Ϊԭͼһ��
	IplImage *img = cvCreateImage(cvSize(pic->width / 2, pic->height / 2), pic->depth, pic->nChannels);
	cvPyrDown(pic, img);
	//�Ŵ�H��S��V����
	IplImage *out = saturate_SV(img);
	
	//��ʾ
	cvNamedWindow("Out");
	cvShowImage("Out", out);
	cvWaitKey(0);
	return 0;
}