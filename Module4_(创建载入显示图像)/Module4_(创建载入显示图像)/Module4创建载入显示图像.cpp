// Module4创建载入显示图像.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"

int main(int argc, char* argv[])
{
	//创建窗口，载入图像
	IplImage *pic = cvLoadImage("F:\\Watson.jpg");
	cvNamedWindow("Example1", 0);
	//调整窗口大小
	cvResizeWindow("Example1", pic->width/2, pic->height/2);
	//显示图像
	cvShowImage("Example1", pic);
	//保存图像
	cvSaveImage("G:\\Watson.jpg", pic);
	
	//图像转换函数：cvConvertImage();源图像任意，目标图像必须是8位的单通道或3通道
	IplImage *img = cvCreateImage(cvGetSize(pic), IPL_DEPTH_8U, 1);
	cvConvertImage(pic, img, 0);
	cvNamedWindow("Example2", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example2", img);
    
	//键盘事件
	cvWaitKey(0);
    return 0;
}

