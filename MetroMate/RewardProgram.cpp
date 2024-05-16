#include <iostream>
#include<string>
#include"RewardProgram.h"

using namespace std;
int RewardProgram:: points;
RewardProgram :: RewardProgram()
{
		points=0;
}

RewardProgram::RewardProgram(int point)
{
	points = point;
}

bool RewardProgram:: check_reward()
	{
		if (points == 5)
		{
		
			return true;
		}
		else
			return false;
	}
void RewardProgram:: increment_points() {
	points++;
}
int RewardProgram::getPoints()
{
	return points;
}
void RewardProgram:: redeem_reward()
	{
		points = 0;
		cout << "You completed 5 rides!" << endl;
		cout << "Your next ride is free!" << endl;
	}
