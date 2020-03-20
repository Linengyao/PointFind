// PointFind.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("E:\\课程\\数字图像处理\\图片5.jpg", 0);
	cv::Mat BinaryMat;
	cv::Mat OpenMat;
	cv::Mat statsMat;
	cv::Mat labelMat;
	cv::Mat centrMat;
	cv::Mat ResultMat;
	//二值化
	threshold(srcMat, BinaryMat, 110, 255, THRESH_BINARY_INV);
	
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));		
	morphologyEx(BinaryMat, OpenMat, MORPH_OPEN, element); //开运算

	OpenMat.copyTo(ResultMat);

   //连通域标记
	int nComp = connectedComponentsWithStats(OpenMat,
											labelMat,
											statsMat,
		centrMat,
		8,
		CV_32S);
	//绘制bounding box
	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		//bounding box左上角坐标
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);

		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);

		//绘制
		rectangle(ResultMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("bMat", BinaryMat);
	imshow("OpenMat", OpenMat);
	imshow("resultMat", ResultMat);
	cout << "共有" << nComp - 1 << "个点" << endl;
	waitKey(0);
	return 0;
    //std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
