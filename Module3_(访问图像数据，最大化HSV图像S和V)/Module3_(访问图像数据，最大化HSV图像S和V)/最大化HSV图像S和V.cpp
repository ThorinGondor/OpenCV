#include "highgui.h"
#include "cv.h"

//改变一张图的H、S和V将会改变该图的亮度、饱和度等
IplImage* saturate_SV(IplImage *pic)
{
	IplImage *buff = pic;
	for (int y = 0; y < buff->height; y++)
	{
		uchar* ptr = (uchar*)(buff->imageData + y*buff->widthStep);  //遍历每一行
		for (int x = 0; x < buff->width; x++)  //遍历每一列（每一行的各个元素）
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
	//创建原图pic
	IplImage *pic = cvLoadImage("F:\\DeepSea.jpg");
	//创建img图，缩放为原图一半
	IplImage *img = cvCreateImage(cvSize(pic->width / 2, pic->height / 2), pic->depth, pic->nChannels);
	cvPyrDown(pic, img);
	//放大H、S、V部分
	IplImage *out = saturate_SV(img);
	
	//显示
	cvNamedWindow("Out");
	cvShowImage("Out", out);
	cvWaitKey(0);
	return 0;
}