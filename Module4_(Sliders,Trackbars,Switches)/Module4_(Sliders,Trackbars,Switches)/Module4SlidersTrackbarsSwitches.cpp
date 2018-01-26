// Module4SlidersTrackbarsSwitches.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>
void Trackbar_callback(int position)
{
	switch (position)
	{
	    case 0: {cvShowImage("Demo", cvLoadImage("F:\\FF15.jpg")); }
			break;
	    case 1: {cvShowImage("Demo", cvLoadImage("F:\\Porsche.jpg"));}
		    break;
	    case 2: {cvShowImage("Demo", cvLoadImage("F:\\Ferrari.jpg")); }
		    break;
	    case 3: {cvShowImage("Demo", cvLoadImage("F:\\Watson.jpg")); }
		    break;
	    case 4: {cvDestroyAllWindows(); }
		    break;
	}
}

int main(int argc ,char* argv[])
{
	cvNamedWindow("Demo", CV_WINDOW_AUTOSIZE);
	
	//设置滚动条：
	cvCreateTrackbar("Open-Close", "Demo", 0, 4, Trackbar_callback/**此处调用函数，并会传参给该函数（int类的position）**/);
	
	while (1)
	{
		if(cvWaitKey(15) == 27)
			break;
	}
    return 0;
}

