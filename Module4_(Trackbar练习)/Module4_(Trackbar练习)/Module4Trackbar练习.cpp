// Module4Trackbar练习.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"

void SwitchPhoto(int position)
{
	switch (position)
	{
	case 0: {cvShowImage("PhotoShow", cvLoadImage("F:\\FF15.jpg")); }
			break;
	case 1: {cvShowImage("PhotoShow",cvLoadImage("F:\\Watson.jpg")); }
		break;
	case 2: {cvShowImage("PhotoShow", cvLoadImage("F:\\Ferrari.jpg")); }
			break;
	case 3: {cvShowImage("PhotoShow", cvLoadImage("F:\\porsche.jpg")); }
			break;
	case 4: {cvDestroyAllWindows();}
			break;
	}
}

int main(int argc, char* argv[])
{
	cvNamedWindow("PhotoShow", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Switch Photos", "PhotoShow", 0, 4, SwitchPhoto);
	while (1)
	{
		if (cvWaitKey(15) == 27)
			break;
	}
	return 0;
}

