#pragma once
#include <iostream>
#include<string>
#include <map>
#include<vector>
#include<ctime>
using namespace std;

class Station
{
public:	
	static int numberOfTickets ;
	static double totalIncome ;
	string stationName;
	int line;
	bool line1;
	bool line2;
	bool line3;

	map<std::string, std::pair<int, double>> dailyIncome; // Date -> number of tickets, income
	void read(ifstream* f);
	void write(ofstream* f);
	vector<pair<int, double>> weeklyIncome;
	vector<pair<int, double>> monthlyIncome;
	vector<pair<int, double>> yearlyIncome;
	Station(string name, bool  Line1, bool Line2, bool Line3);
	
	Station();
	string getName();
	int getLine();
	void addData(string date, int numTickets, double income); //daily
	void calculateDailyIncome();
	void calculateWeeklyIncome(); 
	void calculateMonthlyIncome();
	void calculateYearlyIncome();
	string toString();
};

