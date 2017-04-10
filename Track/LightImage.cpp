#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
bool acceptTrackedPoint(int i);

int const MAX_CORNERS = 1200;
CvPoint2D32f * cornerA;
CvPoint2D32f * cornerB;


std::string IntToString(const int index)
{
	std::stringstream ss;
	ss << index;
	return ss.str();
}
std::string ConsFileName(const int index, const std::string bias)
{
	std::string filename = bias;
	filename += "/";
	filename += IntToString(index);
	filename += ".jpg";
	return filename;
}
void MatToImage(cv::Mat &src_img, const std::string  file_name)
{
	std::vector<unsigned char>buff;
	cv::imencode(".jpg", src_img, buff);
	ofstream in;
	in.open(file_name);
	for (int j = 0; j<buff.size(); j++){
		in << buff[j];
	}
	in.close();
}

int main(int argc, char **argv)
{

	VideoCapture pCapture(0);


	IplImage *pre_frame;  //the previous frame 
	IplImage *cur_frame;  //the current frame
	IplImage *dst_img;   //the result 
	IplImage *cur_img;
	IplImage *pre_img;

	cornerA = new CvPoint2D32f[MAX_CORNERS];
	cornerB = new CvPoint2D32f[MAX_CORNERS];
	char *features_found = new char[MAX_CORNERS];
	float *features_error = new float[MAX_CORNERS];
	CvTermCriteria criteria;
	criteria = cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 64, 0.01);
	// 获取前一帧
	//pre_frame = cvQueryFrame(capture);
	cv::Mat we_img;
	IplImage we;

	pCapture >> we_img;
	 we = we_img;
	pre_frame = cvCloneImage(&we);
	int index = 0;


	while (1)
	{
		++index;
		// 获取当前帧
		//cur_frame = cvQueryFrame(capture);

		pCapture >> we_img;
		we = we_img;
		cur_frame = cvCloneImage(&we);

		if (!cur_frame)
		{
			cout << "No frame is captured ! \n";
			break;
		}

		int i, j;
		int point_number = 0;
		int rows, cols;
		int countn = MAX_CORNERS;

		CvSize img_sz = cvGetSize(cur_frame);
		pre_img = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
		cvCvtColor(pre_frame, pre_img, CV_RGB2GRAY);

		cur_img = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
		cvCvtColor(cur_frame, cur_img, CV_RGB2GRAY);
		dst_img = (IplImage *)cvClone(cur_frame);

		IplImage *move_img = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
		cvZero(move_img);
		cols = cur_frame->width;
		rows = cur_frame->height;
		for (i = 0; i <cols; i++)
		{
			for (j = 0; j<rows; j++)
			{
				// 如果前后两帧的同一个像素点的值之差大于阈值，则认为该像素运动了
				double a = abs(cvGet2D(pre_img, j, i).val[0] - cvGet2D(cur_img, j, i).val[0]);
				CvScalar b = cvScalar(a, 0, 0, 0);
				// 设置灰度图像
				cvSet2D(move_img, j, i, b);
				if (a>40)
				{
					if (point_number<MAX_CORNERS - 1)
					{
						cornerA[++point_number].x = i;
						cornerA[point_number].y = j;
					}
				}
			}
		}


		 cv::Mat src_img = cv::cvarrToMat(move_img); 
		 cv::imshow("wemadefox", src_img);
	//	 MatToImage(src_img,ConsFileName(index,"move")); 

		CvSize Pyrsize = cvSize(pre_img->width + 8, pre_img->height / 3);
		IplImage * pyrA = cvCreateImage(Pyrsize, IPL_DEPTH_32F, 1);
		IplImage * pyrB = cvCreateImage(Pyrsize, IPL_DEPTH_32F, 1);

		cvCalcOpticalFlowPyrLK(pre_img, cur_img, pyrA, pyrB, cornerA, cornerB, countn,
			cvSize(10, 10), 3, features_found, features_error, criteria, 0);
		for (i = 0; i < countn; i++)
		{
			if (features_found[i] && acceptTrackedPoint(i))
			{
				cvLine(dst_img, cvPointFrom32f(cornerA[i]), cvPointFrom32f(cornerB[i]), CV_RGB(0, 255, 0), 1, CV_AA, 0);
				//cvCircle(dst_img,cvPointFrom32f (cornerB[i]), 3,  CV_RGB (255, 0, 0), -1);
			}
			// 交换角点数据
			cornerA[i] = cornerB[i];
		}
		// 当前帧交换到前一帧
		pre_frame = (IplImage *)cvClone(cur_frame);

		cv::Mat sr_img = cv::cvarrToMat(dst_img);
		cv::imshow("wemadox", sr_img);
//		MatToImage(sr_img,ConsFileName(index,"dst")) ;

		cvWaitKey(1);
		cvReleaseImage(&dst_img);
		cvReleaseImage(&pyrA);
		cvReleaseImage(&pyrB);
		cvReleaseImage(&move_img);


	}

	cvReleaseImage(&pre_frame);
	cvReleaseImage(&cur_frame);

	cvReleaseImage(&pre_img);
	cvReleaseImage(&cur_img);

	return 0;
}
// 通过设定之前点与当前点的距离来判断特征点是否可以获取
bool acceptTrackedPoint(int i)
{
	return ((abs(cornerA[i].x - cornerB[i].x) + abs(cornerA[i].y - cornerB[i].y)) > 30);
}
