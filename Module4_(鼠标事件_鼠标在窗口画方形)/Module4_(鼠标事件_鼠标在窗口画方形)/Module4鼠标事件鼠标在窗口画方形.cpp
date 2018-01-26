// Module4鼠标事件鼠标在窗口画方形.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"

CvRect box;

bool drawing_box = false;

void draw_box(IplImage *img,CvRect rect)   //该函数使用cvRectangle();绘制box矩形
{
	cvRectangle(
		img, 
		CvPoint(box.x, box.y),
		CvPoint(box.x + box.width, box.y + box.height),
		CvScalar(0,0,255)
	);
}
void custom_mouse_callback(int event,int x,int y,int flags,void* param) //该函数定义了鼠标事件
{
	IplImage *image = (IplImage*)param;
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE: 
	{
		if (drawing_box) { box.width = x - box.x; box.height = y - box.y; }
	}
		break;
	case CV_EVENT_LBUTTONDOWN: 
	{
		drawing_box = true;
		box = cvRect(x, y, 0, 0);
	}
	    break;
	case CV_EVENT_LBUTTONUP:
	{
		drawing_box = false;
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0)
		{
			box.y += box.height;
			box.height *= -1;
		}
		draw_box(image, box);
	}
	}
}


int main(int argc,char* argv[])
{
	box = CvRect(-1,-1,0,0);
	IplImage *pic = cvLoadImage("F:\\Porsche.jpg");
	IplImage *buff = cvCloneImage(pic);  //pic克隆到buff
	cvNamedWindow("Box_Example",CV_WINDOW_AUTOSIZE);
	//设置鼠标事件
	cvSetMouseCallback("Box_Example", custom_mouse_callback, (void*)pic);

	while (1)
	{
		cvRepeat(pic, buff);
		if (drawing_box)
			draw_box(buff, box);
		cvShowImage("Box_Example", buff);

		if (cvWaitKey(15) == 27)
			break;
	}

    return 0;
}

