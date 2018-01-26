#include "highgui.h"
#include "cv.h"

int main(int argc, char* argv[])
{
	//载入两张原图，我们只需要对两张图各自的感兴趣区域进行融合，因此这里设置了两个感兴趣区域
	IplImage *src1 = cvLoadImage("F:\\watchdog1.jpg");
	IplImage *src2 = cvLoadImage("F:\\watchdog2.jpg");
	cvSetImageROI(src1, CvRect(150, 200, 500, 500));
	cvSetImageROI(src2, CvRect(800, 180, 500, 500));

	//图片融合，只对这两个感兴趣区域融合，融合完以后取消src1的感兴趣区域，这样src1的图片就能在下一阶段全部显示了
	double alpha = 0.4;
	double beta = 0.6;
	cvAddWeighted(src1, alpha, src2, beta, 0, src1);
	cvResetImageROI(src1);

	//打印输出
	cvNamedWindow("out_pictrue",CV_WINDOW_AUTOSIZE);
	cvShowImage("out_pictrue", src1);
	cvWaitKey(0);

	cvDestroyWindow("out_pictrue");
	cvReleaseImage(&src1);
	cvReleaseImage(&src2);
	return 0;
}