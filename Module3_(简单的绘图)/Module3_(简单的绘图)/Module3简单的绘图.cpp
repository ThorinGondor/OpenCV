// Module3简单的绘图.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cv.h"
#include "highgui.h"

int main(int argc, char* argv[])
{
	IplImage *pic = cvLoadImage("F:\\Porsche.jpg");

	//在图片上画一条线： cvLine();函数方法
	cvLine(pic, CvPoint(200, 200), CvPoint(400, 400), CvScalar(170,100), 2, 8);
	//在图片上画一个矩形： cvRectangle();函数方法
	cvRectangle(pic,CvPoint(300,300),CvPoint(400,400),CvScalar(80,60),2,8);
	//画一个圆形
	cvCircle(pic, CvPoint(450, 450), 50, CvScalar(100, 170), 2, 8);
	//画一个椭圆
	cvEllipse(pic, CvPoint(500, 500), CvSize(200, 50), 30.0, 0, 360, CvScalar(40, 30, 70), 2, 8);
	//画一个多边形
	
	//写一段文字
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 1, 2, 8); //CvFont &font,字体，hscale，vscale，shear斜体字，粗细，8平滑度
	cvPutText(pic, "Kimi Raikkonen", CvPoint(100, 100), &font, CvScalar(40, 30, 120));

	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example1", pic);
	cvWaitKey(0);
    return 0;
}

