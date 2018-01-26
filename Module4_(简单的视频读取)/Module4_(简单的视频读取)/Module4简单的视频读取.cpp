// Module4简单的视频读取.cpp: 定义控制台应用程序的入口点。
/****
   步骤：
   （1）先建立视频captrue（全局），载入一个视频。
   （2）建立一个空图，用于显示帧。
   （3）创建滑动条，获取视频的总帧数（cvGetCaptureProperty();)，同时该创建会调用一个函数（会把当前的position传参），被调用的函数里将会设置视频属性（更改播放进度）
   （4）进入循环，读取视频下一帧（cvQueryFrame();)，并显示
****/

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"
#include <iostream>

//全局变量
CvCapture *captrue = cvCreateFileCapture("F:\\1.mkv");//载入一个视频

inline void AdjustProgress(int pos)
{
	cvSetCaptureProperty(captrue, CV_CAP_PROP_POS_FRAMES, pos);  //更改播放进度
}

int main(int argc, char* argv[])
{
	std::cout << "hhh" << std::endl;
	IplImage *frame;  //建立一个图片，专门用于视频的每一帧图像
	cvNamedWindow("Film", CV_WINDOW_AUTOSIZE);
	int frames = (int)cvGetCaptureProperty(captrue, CV_CAP_PROP_FRAME_COUNT); //获取视频的总帧数
	cvCreateTrackbar("Progress", "Film", 0, frames, AdjustProgress);
	while (true)
	{
		frame = cvQueryFrame(captrue); //获取视频的下一帧图片
		cvShowImage("Film", frame);
		if (cvWaitKey(33) == 27)
			break;
	}

	cvDestroyWindow("Film");
	cvReleaseCapture(&captrue);
	cvWaitKey(0);

    return 0;
}

