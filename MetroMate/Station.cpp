#include "Station.h"
#include <string>
#include<iostream>
#include<fstream>
#include<sstream>

 int Station:: numberOfTickets=0;
 double Station::totalIncome=0;
void Station::read(ifstream* f)
{
    string line;
    while (getline(*f, line)) {
        stringstream ss(line);
        string num1, num2,date;
        getline(ss, date, ',');
        getline(ss, num1, ',');
        getline(ss, num2, ',');

        addData(date, stoi(num1), stod(num2));
      
    }
}
void Station::write(ofstream* f)
{
    
    for (auto it = dailyIncome.begin(); it != dailyIncome.end(); it++) {
      
        (*f) << it->first << "," << to_string(it->second.first) << "," << to_string(it->second.second) << "\n";
        
    }
    (*f) << "-"<<"\n";
   
}
Station::Station(string name, bool  Line1, bool Line2,bool Line3)
{
	
	stationName = name;
	line1 = Line1;
	line2 = Line2;
	line3 = Line3;

	
}
Station::Station()
{
}

string Station::getName()
{
	return stationName;
}

int Station::getLine()
{
	return line;
}


void Station::addData(string date, int numTickets, double income) {
    dailyIncome[date] = make_pair(numTickets, income);
}

void Station::calculateDailyIncome() {
    cout << "Daily Income for " << stationName << ":" << endl;
    for (auto it = dailyIncome.begin(); it != dailyIncome.end(); it++) {
        cout << "Date: " << it->first << ", Tickets: " << it->second.first
            << ", Income: " << it->second.second << endl;
    }
}

void Station::calculateWeeklyIncome() {

    weeklyIncome.clear();

    for (auto it = dailyIncome.begin(); it != dailyIncome.end(); it++)
    {
        string date = it->first;
        int numTickets = it->second.first;
        double income = it->second.second;
        cout << date << endl;
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        cout << year << " " << month << " "<<day<<endl;
        int dayOfYear = (month - 1) * 30 + day;
        int week = (dayOfYear - 1) / 7 + 1;


        if (week >= weeklyIncome.size()) {
            weeklyIncome.resize(week + 1, { 0, 0.0 });
        }

     
        weeklyIncome[week - 1].first += numTickets;
        weeklyIncome[week - 1].second += income;
    }

    // Output
    cout << "Weekly Income for " << stationName << ":" << endl;
    for (auto it = weeklyIncome.begin(); it != weeklyIncome.end(); it++) {
        if (it->second != 0) {
            cout << "Week " << distance(weeklyIncome.begin(), it) + 1
                << ", Tickets: " << it->first << ", Income: " << it->second << endl;
        }
    }
}

void Station::calculateMonthlyIncome()
{

    monthlyIncome = vector<pair<int, double>>(12, { 0, 0.0 });

    for (auto it = dailyIncome.begin(); it != dailyIncome.end(); it++) {
        string date = it->first;
        int numTickets = it->second.first;
        double income = it->second.second;

        int month = stoi(date.substr(5, 2));

        monthlyIncome[month - 1].first += numTickets;
        monthlyIncome[month - 1].second += income;
    }

    // Output
    cout << "Monthly Income for " << stationName << ":" << endl;
    for (auto it = monthlyIncome.begin(); it != monthlyIncome.end(); it++) {
        if (it->second != 0) {
            cout << "Month " << distance(monthlyIncome.begin(), it) + 1
                << ", Tickets: " << it->first << ", Income: " << it->second << endl;
        }
    }
}
void Station::calculateYearlyIncome() {

    yearlyIncome = vector<pair<int, double>>(1, { 0, 0.0 });

    for (auto it = dailyIncome.begin(); it != dailyIncome.end(); it++) {
        int numTickets = it->second.first;
        double income = it->second.second;

        yearlyIncome[0].first += numTickets;
        yearlyIncome[0].second += income;
    }

    // Output
    cout << "Yearly income for " << stationName << ":" << endl << "Tickets: " << yearlyIncome[0].first
        << ", Income: " << yearlyIncome[0].second << endl;
}


string Station::toString()
{

	string sline1, sline2, sline3;
	if (line1) {
		sline1 = "true";
	}
	else {
		sline1 = "false";
	}
	if (line2) {
		sline2 = "true";
	}
	else {
		sline2 = "false";
	}if (line3) {
		sline3 = "true";
	}
	else {
		sline3 = "false";
	}
	return stationName + "," + sline1 + "," + sline2 + "," + sline3;
}
