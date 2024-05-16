#include "Ride.h"
#include<iostream>
#include<string>
#include <chrono>
#include <thread>
#include <algorithm>
#include<vector>
#include"RewardProgram.h"

using namespace std;

Ride::Ride(string startSt, string endSt, string date)
{
    start_station = startSt;
    end_station = endSt;
    currentDate = stringToTimePoint(date);

}
Ride::Ride(string startSt, string endSt)
{
    start_station = startSt;
    end_station = endSt;
    currentDate = chrono::system_clock::now();

}
Ride::Ride() {


}
auto Ride::getCurrentDate() {
    writedate = std::chrono::system_clock::now();
    time_t start_date = chrono::system_clock::to_time_t(writedate);
    tm  tm_start_date;
    if (localtime_s(&tm_start_date, &start_date) != 0) {
        cerr << "failed to convert time " << endl;
    }
    return   put_time(&tm_start_date, "%y-%m-%d");
}


void Ride::display()
{
    cout << "Start Station: " << start_station << endl;
    cout << "End Station: " << end_station << endl;
    
    cout << "Date: " << timePointToString(currentDate) <<endl;
  
}
string Ride::toString()
{
    return start_station + "," + end_station + "," + timePointToString(currentDate);
}


std::string Ride::timePointToString(const std::chrono::system_clock::time_point& tp)
{
    std::time_t time = std::chrono::system_clock::to_time_t(tp);

    // Convert time_t to tm struct safely
    std::tm timeStruct;
    localtime_s(&timeStruct, &time);  // Safe version of localtime for Windows

    // Use stringstream to format the date as a string
    std::stringstream ss;
    ss << std::put_time(&timeStruct, "%Y-%m-%d");

    // Return the formatted string
    return ss.str();
}
std::chrono::system_clock::time_point Ride::stringToTimePoint(const std::string& dateTimeStr)
{
    int year, month, day;
    char dash1, dash2;

    std::istringstream iss(dateTimeStr);
    iss >> year >> dash1 >> month >> dash2 >> day;

    // Validate separators
    if (dash1 != '-' || dash2 != '-') {
        throw std::runtime_error("Invalid date format. Expected format is YYYY-MM-DD.");
    }

    // Basic range checks
    if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31) {
        throw std::runtime_error("Date components out of range.");
    }

    // Compute days from 1970 up to the given year, considering leap years
    long days = 0;
    for (int y = 1970; y < year; ++y) {
        days += (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 366 : 365;
    }

    // Days in each month
    std::vector<int> monthDays{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        monthDays[1] = 29; // February in a leap year
    }

    // Add days for the months in the given year
    for (int m = 0; m < month - 1; ++m) {
        days += monthDays[m];
    }

    // Add days for the current month
    days += (day - 1);

    // Calculate total seconds since the epoch at midnight of the given day
    auto seconds_since_epoch = days * 86400LL;

    // Return the time_point based on the seconds since epoch
    return std::chrono::system_clock::time_point(std::chrono::seconds(seconds_since_epoch));


}



