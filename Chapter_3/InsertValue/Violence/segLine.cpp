#include<iostream>
#include<algorithm>
#include<vector>

typedef struct Point
{
	double x;
	double y;
	Point(double x,double y)
	{
		this->x = x;
		this->y = y;
	}
}Point;

std::vector<Point> InsertValue(	Point prefix,Point suff,int number)
{
	double dist_x = (suff.x - prefix.x)/(number);
	double dist_y = (suff.y - prefix.y)/(number);


	std::vector<Point> ans;
	for(int i=1;i<=number;i++)
	{
		ans.push_back(Point(prefix.x + dist_x*i,prefix.y + dist_y*i));
	}
	return ans;
}


int main()
{
	std::vector<Point> ans;
	ans = InsertValue(Point(-20,50),Point(-10,58),5);

	for(int i=0;i<ans.size();i++)
	{
		std::cout<<i<<" "<<ans[i].x<<" "<<ans[i].y<<std::endl;
	}

	ans = InsertValue(Point(-10,58),Point(3,64),5);

	for(int i=0;i<ans.size();i++)
	{
		std::cout<<i<<" "<<ans[i].x<<" "<<ans[i].y<<std::endl;
	}


	ans = InsertValue(Point(3,64),Point(19,67),5);

	for(int i=0;i<ans.size();i++)
	{
		std::cout<<i<<" "<<ans[i].x<<" "<<ans[i].y<<std::endl;
	}

	ans = InsertValue(Point(19,67),Point(30,65),5);

	for(int i=0;i<ans.size();i++)
	{
		std::cout<<i<<" "<<ans[i].x<<" "<<ans[i].y<<std::endl;
	}
	ans = InsertValue(Point(30,65),Point(41,59),5);

	for(int i=0;i<ans.size();i++)
	{
		std::cout<<i<<" "<<ans[i].x<<" "<<ans[i].y<<std::endl;
	}
	ans = InsertValue(Point(41,59),Point(52,51),5);

	for(int i=0;i<ans.size();i++)
	{
		std::cout<<i<<" "<<ans[i].x<<" "<<ans[i].y<<std::endl;
	}
	
	return 0;
}
