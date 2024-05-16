#pragma once
#include<iostream>
#include<string>
#include <ctime>
#include<chrono>
#include<cctype>
#include<iomanip>
#include<sstream>
#include <list>

using namespace std;
class Ride {


public:
	list<Ride>myride;
	string start_station;
	string end_station;
	string ride_date;
	double price;
	double start_time;
	double end_time;
	std::chrono::system_clock::time_point currentDate;
	std::chrono::system_clock::time_point writedate;

	Ride(string startSt, string endSt, string date);
	Ride(string startSt, string endSt);
	Ride();
	std::string timePointToString(const std::chrono::system_clock::time_point& tp);
	std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTimeStr);
	void display();
	void calc_fare(int num_stations_traveled);
	auto getCurrentDate();
	void display_ride_history(const list<Ride>& myride);
	string toString();


};