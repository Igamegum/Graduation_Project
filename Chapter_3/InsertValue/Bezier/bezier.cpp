#include <stdio.h>
#include <iostream>
#include <vector>
#define NUM_STEPS 30 //越大，曲线越密，越逼近
using namespace std;
class CvPoint
{
public:
	float x;
	float y;
	CvPoint()
	{
		x=0.0;
		y=0.0;
	}
	CvPoint(float a,float b)
	{
		x=a;
		y=b;
	}

}; 

void curve4(vector<CvPoint> &p,  
			double x1, double y1,   //Anchor1  
			double x2, double y2,   //Control1  
			double x3, double y3,   //Control2  
			double x4, double y4)   //Anchor2  
{  
	CvPoint tmp0(x1,y1);
	p.push_back(tmp0); 
	double dx1 = x2 - x1;  
	double dy1 = y2 - y1;  
	double dx2 = x3 - x2;  
	double dy2 = y3 - y2;  
	double dx3 = x4 - x3;  
	double dy3 = y4 - y3;  

	double subdiv_step  = 1.0 / (NUM_STEPS + 1);  
	double subdiv_step2 = subdiv_step*subdiv_step;  
	double subdiv_step3 = subdiv_step*subdiv_step*subdiv_step;  

	double pre1 = 3.0 * subdiv_step;  
	double pre2 = 3.0 * subdiv_step2;  
	double pre4 = 6.0 * subdiv_step2;  
	double pre5 = 6.0 * subdiv_step3;  

	double tmp1x = x1 - x2 * 2.0 + x3;  
	double tmp1y = y1 - y2 * 2.0 + y3;  

	double tmp2x = (x2 - x3)*3.0 - x1 + x4;  
	double tmp2y = (y2 - y3)*3.0 - y1 + y4;  

	double fx = x1;  
	double fy = y1;  

	double dfx = (x2 - x1)*pre1 + tmp1x*pre2 + tmp2x*subdiv_step3;  
	double dfy = (y2 - y1)*pre1 + tmp1y*pre2 + tmp2y*subdiv_step3;  

	double ddfx = tmp1x*pre4 + tmp2x*pre5;  
	double ddfy = tmp1y*pre4 + tmp2y*pre5;  

	double dddfx = tmp2x*pre5;  
	double dddfy = tmp2y*pre5;  

	int step = NUM_STEPS;  

	while(step--)  
	{  
		fx   += dfx;  
		fy   += dfy;  
		dfx  += ddfx;  
		dfy  += ddfy;  
		ddfx += dddfx;  
		ddfy += dddfy;  
		CvPoint tmp1(fx,fy);
		p.push_back(tmp1);  
	}  
	CvPoint tmp2(x4,y4);
	p.push_back(tmp2); 
}  

int main()
{
	CvPoint point[7];
	point[0].x=-20.0;
	point[0].y=50.0;
	point[1].x=10.2;
	point[1].y=58.0;
	point[2].x=3;
	point[2].y=64;
	point[3].x=19;
	point[3].y=67;

	point[4].x=30;
	point[4].y=65;
	point[5].x=41;
	point[5].y=59;
	point[6].x=52;
	point[6].y=51;





	for(int index = 0;index<=4;index+=3)
	{
		vector<CvPoint> curvePoint;
		curve4(curvePoint,
				point[index].x,point[index].y,
				point[index+1].x,point[index+1].y,
				point[index+2].x,point[index+2].y,
				point[index+3].x,point[index+3].y
			  );
		int i=0;
		for(;i<curvePoint.size();i++)
		{
			cout<<curvePoint[i].x<<" "<<curvePoint[i].y<<std::endl;
		}
	}

	return 0;
}
