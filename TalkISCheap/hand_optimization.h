#pragma once

const int NUM_STEPS = 30;

std::vector<std::pair<float,float> > curve4( 
		double x1, double y1,   //Anchor1  
		double x2, double y2,   //Control1  
		double x3, double y3,   //Control2  
		double x4, double y4)   //Anchor2  
{  
	std::vector<std::pair<float,float> > ans;
	ans.push_back(std::make_pair(x1,y1));
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
		ans.push_back(std::make_pair(fx,fy));
	}
	  
	ans.push_back(std::make_pair(x4,y4));
	return ans;
}  
