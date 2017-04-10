#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

void tracking(Mat &frame, Mat &output);
bool addNewPoints();
bool acceptTrackedPoint(int i);

string window_name = "optical flow tracking";
Mat gray;	
Mat gray_prev;	
vector<Point2f> points[2];
vector<Point2f> initial;  
vector<Point2f> features; 
int maxCount = 500;	
double qLevel = 0.01;	
double minDist = 10.0;	
vector<uchar> status;	
vector<float> err;

int main()
{
	Mat frame;
	Mat result;

//	VideoCapture capture("bike.avi");
	VideoCapture capture(0);

	if(capture.isOpened())
	{
		while(true)
		{
			capture >> frame;

			if(!frame.empty())
			{ 
				tracking(frame, result);
			}
			else
			{ 
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			int c = waitKey(100);
			if( (char)c == 27 )
			{
				break; 
			} 
		}
	}
	return 0;
}

void tracking(Mat &frame, Mat &output)
{
	cvtColor(frame, gray, CV_BGR2GRAY);
	frame.copyTo(output);
	if (addNewPoints())
	{
		goodFeaturesToTrack(gray, features, maxCount, qLevel, minDist);
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());
	}

	if (gray_prev.empty())
	{
		gray.copyTo(gray_prev);
	}
	calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
	int k = 0;
	for (size_t i=0; i<points[1].size(); i++)
	{
		if (acceptTrackedPoint(i))
		{
			initial[k] = initial[i];
			points[1][k++] = points[1][i];
		}
	}
	points[1].resize(k);
	initial.resize(k);
	for (size_t i=0; i<points[1].size(); i++)
	{
		line(output, initial[i], points[1][i], Scalar(0, 0, 255));
		circle(output, points[1][i], 3, Scalar(255, 0, 0), -1);
	}

	swap(points[1], points[0]);
	swap(gray_prev, gray);

	imshow(window_name, output);
}

bool addNewPoints()
{
	return points[0].size() <= 10;
}

bool acceptTrackedPoint(int i)
{
	return status[i] && ((abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2);
}
