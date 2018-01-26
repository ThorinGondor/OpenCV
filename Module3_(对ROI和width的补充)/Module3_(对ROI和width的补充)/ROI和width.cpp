#include "highgui.h"
#include "cv.h"

int main(int argc,char* argv[])
{
	//载入一张图，缩放
	IplImage *origin = cvLoadImage("F:\\Porsche.jpg");
	assert(origin->width % 2 == 0 && origin->height % 2 == 0);
	IplImage *pic = cvCreateImage(cvSize(origin->width / 2, origin->height / 2), origin->depth, origin->nChannels);
	cvPyrDown(origin, pic);

	//设置ROI，需调用方法：cvSetImageROI();
	int x = 50;
	int y = 50;
	int width = 200;
	int height = 200;
	int add = 100;
	cvSetImageROI(pic,cvRect(x,y,width,height));//设置感兴趣区域
	cvAddS(pic, cvScalar(add), pic);  //这样，在这里用cvAddS();方法添加scalar的RGB数值时，仅限于该区域中,其他区域不受影响

	//处理完成后要取消ROI，需调用方法：cvResetImageROI();
	cvResetImageROI(pic);
	//打印输出
	cvNamedWindow("Out_Pictrue", CV_WINDOW_AUTOSIZE);
	cvShowImage("Out_Pictrue", pic);

	cvWaitKey(0);
	return 0;
}