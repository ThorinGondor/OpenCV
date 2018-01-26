// Module3往硬盘写配置文件.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//先创建一个CvFileStorage结构，然后通过cvOpenFileStorage来从磁盘读取数据
	CvFileStorage *FS = cvOpenFileStorage("F:\\cfg.xml", 0, CV_STORAGE_WRITE);
	//写入整形int类数据
	cvWriteInt(FS, "frame_count", 10);
	//写入任意数据结构
	cvStartWriteStruct(FS, "frame_size", CV_NODE_SEQ);
	cvWriteInt(FS, 0, 320);
	cvWriteInt(FS, 0, 200);
	cvEndWriteStruct(FS);
	
	cvReleaseFileStorage(&FS);
	cvWaitKey(0);
    return 0;
}

