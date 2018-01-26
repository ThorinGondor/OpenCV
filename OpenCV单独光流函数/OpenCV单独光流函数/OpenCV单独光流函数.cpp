// OpenCV单独光流函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdafx.h"
#include "highgui.h"
#include "opencv2/video/tracking.hpp"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

	// 参数说明如下：
	// _prev0：输入前一帧图像
	// _next0：输入后一帧图像
	// _flow0：输出的光流
	// pyr_scale：金字塔上下两层之间的尺度关系
	// levels：金字塔层数
	// winsize：均值窗口大小，越大越能denoise并且能够检测快速移动目标，但会引起模糊运动区域
	// iterations：迭代次数
	// poly_n：像素领域大小，一般为5，7等
	// poly_sigma：高斯标注差，一般为1-1.5
	// flags：计算方法。主要包括OPTFLOW_USE_INITIAL_FLOW和OPTFLOW_FARNEBACK_GAUSSIAN

	// OpenCV中此函数源码
void cv::calcOpticalFlowFarneback(InputArray _prev0, InputArray _next0,InputOutputArray _flow0, double pyr_scale, int levels, int winsize,int iterations, int poly_n, double poly_sigma, int flags)
{
#ifdef HAVE_OPENCL
	bool use_opencl = ocl::useOpenCL() && _flow0.isUMat();
	if (use_opencl && ocl_calcOpticalFlowFarneback(_prev0, _next0, _flow0, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags))
	{
		CV_IMPL_ADD(CV_IMPL_OCL);
		return;
	}
#endif
	// 将_prev0和_next0转换为Mat类型
	Mat prev0 = _prev0.getMat(), next0 = _next0.getMat();
	const int min_size = 32;
	// 创建img指针数组，img[0]指向prev0，img[1]指向next0
	const Mat* img[2] = { &prev0, &next0 };

	int i, k;
	double scale;
	Mat prevFlow, flow, fimg;
	// 检查prev0和next0是否大小相同、单通道图像，金字塔尺度关系pyr_scale小于1
	CV_Assert(prev0.size() == next0.size() && prev0.channels() == next0.channels() &&
		prev0.channels() == 1 && pyr_scale < 1);
	// 创建和prev0大小相同，32位浮点双通道图像
	_flow0.create(prev0.size(), CV_32FC2);
	// 将_flow0转换成Mat类型
	Mat flow0 = _flow0.getMat();
	// 循环确定金字塔层数
	for (k = 0, scale = 1; k < levels; k++)
	{
		// scale用于存放第k层图像与原图的尺寸广西
		scale *= pyr_scale;
		// 判断第k层图像行数与min_size关系，确定金字塔层数结束
		if (prev0.cols*scale < min_size || prev0.rows*scale < min_size)
			break;
	}
	// 将计算出的金字塔层数k赋给levels
	levels = k;
	// 遍历金字塔层数
	for (k = levels; k >= 0; k--)
	{
		// 计算原图与k-1层图像的尺寸关系
		for (i = 0, scale = 1; i < k; i++)
			scale *= pyr_scale;
		// 定义高斯滤波系数
		double sigma = (1. / scale - 1)*0.5;
		int smooth_sz = cvRound(sigma * 5) | 1;
		// 得到高斯滤波器模板大小
		smooth_sz = std::max(smooth_sz, 3);
		// 计算第k层图像矩阵的列数
		int width = cvRound(prev0.cols*scale);
		// 计算第k层图像矩阵的行数
		int height = cvRound(prev0.rows*scale);

		if (k > 0)
			// 创建第k层图像尺寸大小的32位双通道图像，用于存储第k层图像光流flow
			flow.create(height, width, CV_32FC2);
		else
			// 否则为原图像
			flow = flow0;
		// 如果preFlow未指向任何矩阵数据
		if (prevFlow.empty())
		{
			// 如果flags为OPTFLOW_USE_INITIAL_FLOW
			if (flags & OPTFLOW_USE_INITIAL_FLOW)
			{
				// 改变flow0图像大小为flow，用像素关系重采样插值
				// 插值使用錓NTER_AREA，主要是为了避免波纹出现
				resize(flow0, flow, Size(width, height), 0, 0, INTER_AREA);
				// 将flow缩小scale
				flow *= scale;
			}
			// flags为OPTFLOW_FARNEBACK_GAUSSIAN
			else
				// 创建一个Mat给flow
				flow = Mat::zeros(height, width, CV_32FC2);
		}
		else
		{
			// 改变prevFlow图像大小为flow，利用INTER_LINEAR方式进行双线性插值
			resize(prevFlow, flow, Size(width, height), 0, 0, INTER_LINEAR);
			// 将flow增加(1./pyr_sacle)倍
			flow *= 1. / pyr_scale;
		}

		Mat R[2], I, M;
		for (i = 0; i < 2; i++)
		{
			// 将img[i]转换为CV_32F格式
			img[i]->convertTo(fimg, CV_32F);
			// 对输出图像fimg进行高斯滤波后用fimg输出
			GaussianBlur(fimg, fimg, Size(smooth_sz, smooth_sz), sigma, sigma);
			// 改变fimg图像大小I,使用双线性插值INTER_LINEAR
			resize(fimg, I, Size(width, height), INTER_LINEAR);
			// 计算邻域图像R[i]，分别得到了视频前后帧中每个像素点的系数向量
			FarnebackPolyExp(I, R[i], poly_n, poly_sigma);
		}
		// 依据R[0]、R[1]、flow等信息更新矩阵M，利用系数向量计算得到光流场
		FarnebackUpdateMatrices(R[0], R[1], flow, M, 0, flow.rows);

		for (i = 0; i < iterations; i++)
		{
			// flags为OPTFLOW_FARNEBACK_GAUSSIAN
			if (flags & OPTFLOW_FARNEBACK_GAUSSIAN)
				// 利用R[0]、R[1]、M等，利用高斯平滑原理，更新光流flow
				FarnebackUpdateFlow_GaussianBlur(R[0], R[1], flow, M, winsize, i < iterations - 1);
			// flags为OPTFLOW_USE_INITIAL_FLOW
			else
				// 利用R[0]、R[1]、M等初始化光流flow
				FarnebackUpdateFlow_Blur(R[0], R[1], flow, M, winsize, i < iterations - 1);
		}
		// 将flow赋给prevFlow
		prevFlow = flow;
	}
}

int main(int argc, char* argv[])
{
    return 0;
}

