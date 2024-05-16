#pragma once
class RewardProgram {
public:
	static int points;
	RewardProgram();
	RewardProgram(int point);
	bool check_reward();
	void redeem_reward();
	void increment_points();
	int getPoints();
};