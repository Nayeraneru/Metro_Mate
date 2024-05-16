#include "Subscription.h"
//#include"Admin.h"
#include<sstream>
#include<fstream>
#include <ctime>
#include<vector>
#include<iomanip>

 int Subscription:: stage1_fee_student = 33;
int Subscription:: stage2_fee_student = 41;
 int Subscription::stage3_fee_student = 50;
int Subscription::stage4_fee_student = 65;

int Subscription::stage1_fee_public_month = 230;
int Subscription::stage2_fee_public_month = 290;
int Subscription::stage3_fee_public_month = 340;
int Subscription::stage4_fee_public_month = 450;

int Subscription::stage1_fee_public_year = 1500;
int Subscription:: stage2_fee_public_year = 2500;
int Subscription:: stage3_fee_public_year = 3500;
int Subscription:: stage4_fee_public_year = 4500;

vector<Subscription::NewSubscription>Subscription::newSubscription;
Subscription::Subscription() {
	balance = 0;
	numberOfTrips = 0;
	subscriptiontype = SubscriptionType::NONE;
}
void Subscription::ChooseSubscription() {
	int stageNumber;
	string type;
	bool subscriptionFlag = false;
	char confirm = 'n';
	int number;

	while (subscriptionFlag == false) {

		cout << "====================" << endl;
		cout << "Write The  Subscription Type:" << endl;
		cout << "1. STUDENT " << endl;
		cout << "2. PUBLIC  " << endl;
		cout << "3. CASH    " << endl;
		cout << "4. NEW   " << endl;
		cout << "Type EXIT To Return To The Main Menu " << endl;
		cout << "====================" << endl;

		cout << "Subscription Type : ";
		cin >> type;
		for (char& c : type) {
			c = tolower(c);
		}

		if (type == "student" && studentFlag) {
			cout << "----------" << endl;
			cout << "Stage 1. Provide Station From 1 => 9" << endl;
			cout << "Stage 2. Provide Station From 10 => 16" << endl;
			cout << "Stage 3. Provide Station From 17=> 23" << endl;
			cout << "Stage 4. Provide Station Gratear Than 23" << endl;
			cout << "----------" << endl;
			cout << "Number of Trips will be "<<numberOfTrips << endl;
			cout << "The duration of Subscription will be "<<studentDuration <<"months" << endl;
			cout << "----------" << endl;
			cout << "The higher The Stage The Subscription Fee Will be More Expensive!!!" << endl;
			cout << "----------" << endl;
			cout << "Enter The Stage Number :";

			while (true) {
				cin >> stageNumber;
				if (cin.fail()) {
					cout << "Invalid, Please try again." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else if (stageNumber == 1) {
					cout << "The Subscription Fee Will Be :"<<stage1_fee_student <<"LE" << endl;
					cout << "Enter Y to Confirm OR Enter N to Decline : ";
					cin >> confirm;
					if (confirm == 'Y' || confirm == 'y') {
						subscriptiontype = SubscriptionType::STUDENT;
						subscriptionFlag = true;
						stage_number = 1;
						break;
					}
					else {
						cout << "returning to subscription page....." << endl;
						break;
					}

				}
				if (stageNumber == 2) {
					cout << "The Subscription Fee Will Be :" << stage2_fee_student << "LE" << endl;
					cout << "Enter Y to Confirm OR Enter N to Decline : ";
					cin >> confirm;
					if (confirm == 'Y' || confirm == 'y') {
						subscriptiontype = SubscriptionType::STUDENT;
						subscriptionFlag = true;
						stage_number = 2;

						break;
					}
					else {
						cout << "returning to subscription page....." << endl;
						break;
					}
				}
				if (stageNumber == 3) {
					cout << "The Subscription Fee Will Be :" << stage3_fee_student << "LE" << endl;
					cout << "Enter Y to Confirm OR Enter N to Decline : ";
					cin >> confirm;
					if (confirm == 'Y' || confirm == 'y') {
						subscriptiontype = SubscriptionType::STUDENT;
						subscriptionFlag = true;
						stage_number = 3;

						break;
					}
					else {
						cout << "returning to subscription page....." << endl;
						break;
					}
				}
				if (stageNumber == 4) {
					cout << "The Subscription Fee Will Be :" << stage4_fee_student << "LE" << endl;					cout << "Enter Y to Confirm OR Enter N to Decline : ";
					cin >> confirm;
					if (confirm == 'Y' || confirm == 'y') {
						subscriptiontype = SubscriptionType::STUDENT;
						subscriptionFlag = true;
						stage_number = 4;

						break;
					}
					else {
						cout << "returning to subscription page....." << endl;
						break;
					}
				}
			}
		}
		else if (type == "student" && studentFlag == false) {
			cout << "sorry this subscription plan is not available right now" << endl;
			break;
		}
		else if (type == "public") {
			cout << "----------" << endl;
			cout << "Stage 1. Provide Station From 1 => 9" << endl;
			cout << "Stage 2. Provide Station From 10 => 16" << endl;
			cout << "Stage 3. Provide Station From 17=> 23" << endl;
			cout << "Stage 4. Provide Station Gratear Than 23" << endl;
			cout << "----------" << endl;
			cout << "1." << publicMonthDuration << " month subscription : Number of Trips will be " << publicMonthTrips << endl;
			cout << "2." << publicYearDuration << " month subscription : Number of Trips will be " << publicYearTrips << endl;
			cout << "----------" << endl;
			cout << "The higher The Stage The Subscription Fee Will be More Expensive!!!" << endl;
			cout << "----------" << endl;
			cout << "Enter The subscription plan: ";
			cin >> number;
			if (cin.fail()) {
				cout << "Invalid, Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (number == 1 && publicMonthFlag) {
				cout << "Enter the number of stages : ";
				while (true) {
					cin >> stageNumber;
					if (stageNumber == 1) {
						cout << "The Subscription Fee Will Be : "<<stage1_fee_public_month<<" LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_MONTH;
							subscriptionFlag = true;
							stage_number = 1;

							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
					if (stageNumber == 2) {
						cout << "The Subscription Fee Will Be : " << stage2_fee_public_month << " LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_MONTH;
							subscriptionFlag = true;
							stage_number = 2;

							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
					if (stageNumber == 3) {
						cout << "The Subscription Fee Will Be : " << stage3_fee_public_month << " LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_MONTH;
							subscriptionFlag = true;
							stage_number = 3;
							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
					if (stageNumber == 4) {
						cout << "The Subscription Fee Will Be : " << stage4_fee_public_month << " LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_MONTH;
							subscriptionFlag = true;
							stage_number = 4;
							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
				}
			}
			else if (number == 1 && publicMonthFlag == false) {
				cout << "sorry this subscription plan is not available right now" << endl;
				break;
			}
			else if (number == 2 && publicYearFlag) {
				cout << "Enter the number of stages : ";
				while (true) {
					cin >> stageNumber;
					if (cin.fail()) {
						cout << "Invalid, Please try again." << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					if (stageNumber == 1) {
						cout << "The Subscription Fee Will Be :"<<stage1_fee_public_year<<" LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_YEAR;
							subscriptionFlag = true;
							stage_number = 1;

							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
					if (stageNumber == 2) {
						cout << "The Subscription Fee Will Be :" << stage2_fee_public_year << " LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_YEAR;
							subscriptionFlag = true;
							stage_number = 2;

							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
					if (stageNumber == 3) {
						cout << "The Subscription Fee Will Be :" << stage3_fee_public_year << " LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_YEAR;
							subscriptionFlag = true;
							stage_number = 3;
							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
					if (stageNumber == 4) {
						cout << "The Subscription Fee Will Be :" << stage4_fee_public_year << " LE" << endl;
						cout << "Enter Y to Confirm OR Enter N to Decline : ";
						cin >> confirm;
						if (confirm == 'Y' || confirm == 'y') {
							subscriptiontype = SubscriptionType::PUBLIC_YEAR;
							subscriptionFlag = true;
							stage_number = 4;
							break;
						}
						else {
							cout << "returning to subscription page....." << endl;
							break;
						}
					}
				}
			}
			else if (number == 2 && publicYearFlag == false) {
				cout << "sorry this subscription plan is not available right now" << endl;
				break;
			}
			else {
				cout << "Invalid Option" << endl;
				cout << "returning to subscription page....." << endl;
			}
		}
		else if (type == "cash") {
			cout << "Card limit will be: " << balanceLimit << " LE " << endl;
			cout << "Card isn't limited to a specific period" << endl;
			cout << "Enter Y to Confirm OR Enter N to Decline : ";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y') {
				subscriptiontype = SubscriptionType::CASH;
				subscriptionFlag = true;
			}
			else
				cout << "returning to subscription page....." << endl;
		}
		else if (type == "new") {
			subscriptionFlag = ChooseNewSubscription();
			if (subscriptionFlag) {
				subscriptiontype = SubscriptionType::NEW;
				cout << "you have successfully subscribed" << endl;

			}
			else
				cout << "returning to subscription page....." << endl;
		}
		else if (type == "exit")
			break;
		else {
			cout << "Invalid Option please try again" << endl;
			continue;
		}
	}

	if (subscriptionFlag) {

		switch (subscriptiontype) {
		case SubscriptionType::STUDENT: {
			numberOfTrips = studentTrips;
			startDate = std::chrono::system_clock::now();
			endtDate = startDate + std::chrono::hours(24 * 30 * studentDuration);
			break;
		}
		case SubscriptionType::PUBLIC_MONTH: {

			numberOfTrips = publicMonthTrips;
			startDate = std::chrono::system_clock::now();
			endtDate = startDate + std::chrono::hours(24 * 30 * publicMonthDuration);
			break;
		}
		case SubscriptionType::PUBLIC_YEAR: {
			numberOfTrips = publicYearTrips;
			startDate = std::chrono::system_clock::now();
			endtDate = startDate + std::chrono::hours(24 * 30 * publicYearDuration);
			break;
		}
		case SubscriptionType::CASH:
			break;
		case SubscriptionType::NONE:
			break;
		case SubscriptionType::NEW:
			break;
		default:
			break;
		}
	}

}

int Subscription::CalculateNumberOfDaysRemaining() {

	auto duration = endtDate - std::chrono::system_clock::now();
	auto days = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
	return static_cast<int> (days);
}

void Subscription::DisplaySubscriptionDetail() {

	time_t start_date = chrono::system_clock::to_time_t(startDate);
	time_t end_date = chrono::system_clock::to_time_t(endtDate);

	tm  tm_start_date;
	if (localtime_s(&tm_start_date, &start_date) != 0) {
		cerr << "failed to convert time " << endl;
	}
	tm tm_end_date;
	if (localtime_s(&tm_end_date, &end_date) != 0) {
		cerr << "failed to convert time " << endl;
	}
	cout << "====================" << endl;
	cout << "Subscription Type : " << ConvertToString(subscriptiontype) << endl;
	if (subscriptiontype == SubscriptionType::CASH) {
		cout << "balance : " << balance << endl;
	}
	else if (subscriptiontype == SubscriptionType::NEW) {
		cout << "Subscription name: " << subscriptionName << endl;
		cout << "Number of trips remaining :" << numberOfTrips << endl;
		cout << "Number of days remaining : " << CalculateNumberOfDaysRemaining() << endl;
		cout << "Start Date : " << put_time(&tm_start_date, "%y-%m-%d") << endl;
		cout << "End Date : " << put_time(&tm_end_date, "%y-%m-%d") << endl;
		cout << "====================" << endl;
	}
	else {
		cout << "Number of trips remaining :" << numberOfTrips << endl;
		cout << "Number of days remaining : " << CalculateNumberOfDaysRemaining() << endl;
		cout << "Start Date : " << put_time(&tm_start_date, "%y-%m-%d") << endl;
		cout << "End Date : " << put_time(&tm_end_date, "%y-%m-%d") << endl;
		cout << "====================" << endl;
	}
}

string Subscription::ConvertToString(SubscriptionType type) {
	switch (type) {
	case SubscriptionType::STUDENT:
		return "STUDENT";
	case SubscriptionType::PUBLIC_MONTH:
		return "PUBLIC";
	case SubscriptionType::PUBLIC_YEAR:
		return "PUBLIC";
	case SubscriptionType::CASH:
		return "CASH";
	case SubscriptionType::NEW:
		return "NEW";

	default:
		return "No subscription found";
	}
}

string Subscription::ConvertToString()
{
	switch (subscriptiontype) {
	case SubscriptionType::STUDENT:
		return "STUDENT";
	case SubscriptionType::PUBLIC_MONTH:
		return "PUBLIC";
	case SubscriptionType::PUBLIC_YEAR:
		return "PUBLIC";
	case SubscriptionType::CASH:
		return "CASH";
	case SubscriptionType::NEW:
		return "NEW";

	default:
		return "No subscription found";
	}
}


void Subscription::ChangeNumberOFTrips() {
	int newTrip;
	int choice;
	string subname;

	do {
		cout << "1.STUDENT" << endl;
		cout << "2.PUBLIC MONTH" << endl;
		cout << "3 PUBLIC YEAR" << endl;
		cout << "4 NEW" << endl;
		cout << "5.EXIT" << endl;
		cout << "Choose Subscription plan: ";
		cin >> choice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		switch (choice) {
		case 1:
			cout << "enter number of trips :";
			cin >> newTrip;
			studentTrips = newTrip;
			cout << "STUDENT NEW TRIPS WILL BE: " << studentTrips << "TRIPS" << endl;
			break;
		case 2:
			cout << "enter number of trips :";
			cin >> newTrip;
			publicMonthTrips = newTrip;
			cout << "PUBLIC MONTH NEW TRIPS WILL BE: " << publicMonthTrips << "TRIPS" << endl;
			break;
		case 3:
			cout << "enter number of trips :";
			cin >> newTrip;
			publicYearTrips = newTrip;
			cout << "PUBLIC YEAR NEW TRIPS WILL BE: " << publicYearTrips << "TRIPS" << endl;
			break;
		case 4:
			if (newSubscription.empty()) {
				cout << "no subscription found " << endl;
				break;
			}
			else {
				cout << "enter subscription name : ";
				cin >> subname;
				for (auto it = newSubscription.begin(); it != newSubscription.end(); it++) {
					if ((*it).name == subname) {
						(*it).newTrips = newTrip;
						cout << "number of trips updated successfully " << endl;
						break;
					}
				}
			}

		default:
			cout << "Invalid subscription type." << endl;
			break;
		}
	} while (choice != 5);
}
void Subscription::writeNew(ofstream* f)
{
	for (int i = 0; i < newSubscription.size(); i++) {
		(*f) << newSubscription[i].newToString() << "\n"; 
	}
}

void Subscription::readWrite(ifstream* f)
{
	string line;
	while (getline(*f, line)) {	

		stringstream ss(line);
		string Name, Duration, newtrips, fees;
		getline(ss, Name, ',');
		getline(ss, Duration, ',');
		getline(ss, newtrips, ',');
		getline(ss, fees, ',');
	
	NewSubscription SUB(Name,stoi(Duration),stoi(newtrips),stoi(fees));
		newSubscription.push_back(SUB);
	}
}
string Subscription::toString()
{

	return to_string(numberOfTrips) + "," + to_string(balance) + "," + ConvertToString() + "," + to_string(stage_number) + "," + timePointToString(startDate) + "," + timePointToString(endtDate);
}
void Subscription::RenewSubscription() {
	string choice;
	int day = CalculateNumberOfDaysRemaining();
	if (subscriptiontype == SubscriptionType::NONE)
		cout << "you dont have subscription" << endl;
	else if (subscriptiontype != SubscriptionType::NONE) {

		if (day != 0)
			cout << "Your Subscription hasn't end yet" << endl;

		cout << "Do you want to Renew your Subscription YES\NO  : ";
		cin >> choice;

		if (choice == "yes" || choice == "YES") {

			switch (subscriptiontype) {
			case SubscriptionType::STUDENT: {
				numberOfTrips = 180;
				startDate = std::chrono::system_clock::now();
				endtDate = startDate + std::chrono::hours(24 * 30 * 3);
				break;
			}
			case SubscriptionType::PUBLIC_MONTH: {

				numberOfTrips = 60;
				startDate = std::chrono::system_clock::now();
				endtDate = startDate + std::chrono::hours(24 * 30 * 1);
				break;
			}
			case SubscriptionType::PUBLIC_YEAR: {
				numberOfTrips = 730;
				startDate = std::chrono::system_clock::now();
				endtDate = startDate + std::chrono::hours(24 * 30 * 12);
				break;
			}
			case SubscriptionType::CASH:
				break;
			case SubscriptionType::NONE:
				break;
			default:
				break;
			}
		}
	}
}
std::string Subscription::timePointToString(const std::chrono::system_clock::time_point& tp)
{
	std::time_t time = std::chrono::system_clock::to_time_t(tp);

	// Convert time_t to tm struct safely
	std::tm timeStruct;
	localtime_s(&timeStruct, &time);  // Safe version of localtime for Windows

	// Use stringstream to format the date as a string
	std::stringstream ss;
	ss << std::put_time(&timeStruct, "%Y-%m-%d ");

	// Return the formatted string
	return ss.str();
}
std::chrono::system_clock::time_point Subscription::stringToTimePoint(const std::string& dateTimeStr)
{
	std::tm tm = {};
	std::istringstream ss(dateTimeStr);

	ss >> std::get_time(&tm, "%Y-%m-%d");
	if (ss.fail()) {
		throw std::runtime_error("Failed to parse the date and time string.");
	}

	// Calculate seconds since the Unix epoch
	const auto years = tm.tm_year + 1900 - 1970; // Years since 1970
	const auto isLeapYear = [](int year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		};

	// Compute the number of days contributed by each year
	long days = 0;
	for (int y = 1970; y < tm.tm_year + 1900; ++y) {
		days += isLeapYear(y) ? 366 : 365;
	}

	// Days in each month of a year
	vector<int> monthDays{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear(tm.tm_year + 1900)) {
		monthDays[1] = 29; // February in a leap year
	}

	// Compute the number of days contributed by each month of the current year
	for (int m = 0; m < tm.tm_mon; ++m) {
		days += monthDays[m];
	}

	// Add the days in the current month
	days += (tm.tm_mday - 1);

	auto hours = days * 24 + tm.tm_hour;
	auto minutes = hours * 60 + tm.tm_min;
	auto seconds = minutes * 60 + tm.tm_sec;

	// Convert the total seconds to a time_point
	return std::chrono::system_clock::time_point(std::chrono::seconds(seconds));

}
void Subscription::UpgradeSubscription() {
	string choice;

	if (subscriptiontype == SubscriptionType::NONE)
		cout << "you dont have subscription" << endl;
	else if (subscriptiontype != SubscriptionType::NONE) {
		cout << "Do you want to cahnge your subscription YES|NO : ";
		cin >> choice;
		if (choice == "yes" || choice == "YES")
			ChooseSubscription();
	}
}
void Subscription::Addbalance() {
	int amount;

	if (subscriptiontype != SubscriptionType::CASH)
		cout << "You can't use balance" << endl;
	else if (balance == balanceLimit)
		cout << "Maximum balance limit has been reached" << endl;
	else {
		cout << "Enter the amount of money you need to your balance (Multiples of ten only!) OR enter zero to exist : ";
		cin >> amount;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if ((amount % 10) != 0)
			cout << "not multiples of ten" << endl;
		else if ((balance + amount) > balanceLimit)
			cout << "the balance has exceeded the limit you can't have more then 400 LE" << endl;
		else if (amount == 0)
			cout << "returning to main menu............." << endl;
		else {
			balance = balance + amount;
			cout << "money added successfully " << endl;
			cout << "The current balance = " << balance << endl;
			cout << "====================" << endl;
		}
	}
}
void Subscription::SubscriptionMenu() {
	int choice;
	do {
		cout << "====================" << endl;
		cout << "1.Subscribe " << endl;
		cout << "2.Show Detials" << endl;
		cout << "3.Renew Subscription" << endl;
		cout << "4.Upgrade Subscription" << endl;
		cout << "5.Add Balance" << endl;
		cout << "6.Exist" << endl;

		cin >> choice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		switch (choice) {
		case 1:
			ChooseSubscription();
			break;
		case 2:
			DisplaySubscriptionDetail();
			break;
		case 3: 
			RenewSubscription();
			break;
		case 4:
			UpgradeSubscription();
			break;
		case 5:
			Addbalance();
			break;
		case 6:
			break;
		default:
			cout << "invalid option!!!\n";
			break;
		}
	} while (choice != 6);
}
void Subscription::RemoveSubscriptionPLan() {
	int choice;
	string subname;
	do {
		cout << "1.STUDENT" << endl;
		cout << "2.PUBLIC MONTH" << endl;
		cout << "3.PUBLIC YEAR" << endl;
		cout << "4.CASH" << endl;
		cout << "5.NEW" << endl;
		cout << "6.EXIT" << endl;
		cout << "Choose Subscription plan to remove from the system: ";
		cin >> choice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		switch (choice) {
		case 1:
			if (studentFlag == false) {
				cout << "the subscription is already removed " << endl;
				break;
			}
			studentFlag = false;
			break;

		case 2:
			if (publicMonthFlag == false) {
				cout << "the subscription is already removed " << endl;
				break;
			}
			publicMonthFlag = false;
			break;

		case 3:
			if (publicYearFlag == false) {
				cout << "the subscription is already removed " << endl;
				break;
			}
			publicYearFlag = false;
			break;

		case 4:
			if (cashFlag == false) {
				cout << "the subscription is already removed " << endl;
				break;
			}
			cashFlag = false;
			break;

		case 5:
			if (newSubscription.empty()) {
				cout << "no subscription to delete " << endl;
				break;
			}
			else {
				cout << "enter subscription name : ";
				cin >> subname;
				for (int i = 0; i < newSubscription.size(); i++) {
					if (newSubscription[i].name == subname) {
						newSubscription.erase(newSubscription.begin()+i);
						cout << "subscription deleted successfully " << endl;
					}
				}
				break;
			}
		default:
			cout << "invalid option!!!\n";
			break;
		}
	} while (choice != 6);
}
void Subscription::UpdateStagePrice() {
	int choice;
	string subname;
	int stageNum;
	int price;

	do {
		cout << "1.STUDENT" << endl;
		cout << "2.PUBLIC MONTH" << endl;
		cout << "3 PUBLIC YEAR" << endl;
		cout << "4 NEW" << endl;
		cout << "5.EXIT" << endl;
		cout << "Choose Subscription plan: ";
		cin >> choice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		switch (choice) {
		case 1:
			cout << "enter stage number :";
			cin >> stageNum;

			switch (stageNum) {
			case 1:
				cout << "enter new price ";
				cin >> price;
				stage1_fee_student = price;
				cout << "new price " << stage1_fee_student << " LE" << endl;
				break;
			case 2:
				cout << "enter new price ";
				cin >> price;
				stage2_fee_student = price;
				cout << "new price " << stage2_fee_student << " LE" << endl;
				break;
			case 3:
				cout << "enter new price ";
				cin >> price;
				stage3_fee_student = price;
				cout << "new price " << stage3_fee_student << " LE" << endl;
				break;
			case 4:
				cout << "enter new price ";
				cin >> price;
				stage4_fee_student = price;
				cout << "new price " << stage4_fee_student << " LE" << endl;
				break;
			default:
				cout << "Invalid stage number." << endl;
			}
			break;
		case 2:
			cout << "enter stage number :";
			cin >> stageNum;

			switch (stageNum) {
			case 1:
				cout << "enter new price ";
				cin >> price;
				stage1_fee_public_month = price;
				cout << "new price " << stage1_fee_public_month << " LE" << endl;
				break;
			case 2:
				cout << "enter new price ";
				cin >> price;
				stage2_fee_public_month = price;
				cout << "new price " << stage2_fee_public_month << " LE" << endl;
				break;
			case 3:
				cout << "enter new price ";
				cin >> price;
				stage3_fee_public_month = price;
				cout << "new price " << stage3_fee_public_month << " LE" << endl;
				break;
			case 4:
				cout << "enter new price ";
				cin >> price;
				stage4_fee_public_month = price;
				cout << "new price " << stage4_fee_public_month << " LE" << endl;
				break;
			default:
				cout << "Invalid stage number." << endl;
			}
			break;
		case 3:
			switch (stageNum) {
			case 1:
				cout << "enter new price ";
				cin >> price;
				stage1_fee_public_year = price;
				cout << "new price " << stage1_fee_public_year << " LE" << endl;
				break;
			case 2:
				cout << "enter new price ";
				cin >> price;
				stage2_fee_public_year = price;
				cout << "new price " << stage2_fee_public_year << " LE" << endl;
				break;
			case 3:
				cout << "enter new price ";
				cin >> price;
				stage3_fee_public_year = price;
				cout << "new price " << stage3_fee_public_year << " LE" << endl;
				break;
			case 4:
				cout << "enter new price ";
				cin >> price;
				stage4_fee_public_year = price;
				cout << "new price " << stage4_fee_public_year << " LE" << endl;
				break;
			default:
				cout << "Invalid stage number." << endl;
			}
			break;
		case 4:
			if (newSubscription.empty()) {
				cout << "no subscription found " << endl;
				break;
			}
			else {
				cout << "enter subscription name : ";
				cin >> subname;
				for (auto it = newSubscription.begin(); it != newSubscription.end(); it++) {
					if ((*it).name == subname) {
						(*it).fee = price;
						cout << "Fee updated successfully " << endl;
						cout << "new price " << (*it).fee << " LE" << endl;
						break;
					}
				}
			}

		default:
			cout << "Invalid subscription type." << endl;
			break;
		}
	} while (choice != 5);
}

void Subscription::ChangeDuration() {
	int newDuration;
	int choice;
	string subname;

	do {
		cout << "1.STUDENT" << endl;
		cout << "2.PUBLIC MONTH" << endl;
		cout << "3 PUBLIC YEAR" << endl;
		cout << "4 PUBLIC YEAR" << endl;
		cout << "5.EXIT" << endl;
		cout << "Choose Subscription plan: ";
		cin >> choice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		switch (choice) {
		case 1:
			cout << "Enter new duration: ";
			cin >> newDuration;
			studentDuration = newDuration;
			cout << "STUDENT DURATION WILL BE " << studentDuration << "MONTHS" << endl;
			break;
		case 2:
			cout << "Enter new duration: ";
			cin >> newDuration;
			publicMonthDuration = newDuration;
			cout << "PUBLIC MONTH DURATION WILL BE " << publicMonthDuration << "MONTHS" << endl;
			break;
		case 3:
			cout << "Enter new duration: ";
			cin >> newDuration;
			publicYearDuration = newDuration;
			cout << "PUBLIC YEAR DURATION WILL BE " << publicYearDuration << "MONTHS" << endl;
			break;
		case 4:
			if (newSubscription.empty()) {
				cout << "no subscription found " << endl;
				break;
			}
			else {
				cout << "enter subscription name : ";
				cin >> subname;
				for (auto it = newSubscription.begin(); it != newSubscription.end(); it++) {
					if ((*it).name == subname) {
						(*it).duration = newDuration;
						cout << "Duration updated successfully " << endl;
						break;
					}
				}
			}
		default:
			break;
		}
	} while (choice != 5);
}
double Subscription::getBalance() {
	return balance;
}
int Subscription::getNumberOfTrips() {
	return numberOfTrips;
}
int Subscription::getStageNumber() {
	return stage_number;
}
void Subscription::AddNewSubscription() {
	NewSubscription SUB;
	cout << "enter subscription name : ";
	cin >> SUB.name;
	cout << "enter duration in months : ";
	cin >> SUB.duration;
	cout << "enter number of trips : ";
	cin >> SUB.newTrips;
	cout << "enter subscription fee : ";
	cin >> SUB.fee;


	newSubscription.push_back(SUB);
}
SubscriptionType Subscription::getType(string type)
{
	if (type == "STUDENT") {
		return SubscriptionType::STUDENT;
	}
	else if (type == "PUBLIC_MONTH") {
		return SubscriptionType::PUBLIC_MONTH;
	}
	else if (type == "PUBLIC_YEAR") {
		return SubscriptionType::PUBLIC_YEAR;

	}
	else if (type == "CASH") {
		return SubscriptionType::CASH;

	}
	else if (type == "NEW") {
		return SubscriptionType::NEW;

	}
	else if (type == "No subscription found") {
		return SubscriptionType::NONE;
	}
}
void Subscription::DisplyNewSubscription() {
	for (int i = 0; i < newSubscription.size(); i++) {
		cout << "Subscription name : " << newSubscription[i].name << endl;
		cout << "Subscription Duration " << newSubscription[i].duration << endl;
		cout << "Subscription Fee " << newSubscription[i].fee << endl;
		cout << "Subscription Trips " << newSubscription[i].newTrips << endl;
	}
}
bool Subscription::ChooseNewSubscription() {
	string subName;
	string choice;
	bool found = false;
	int i;

	if (newSubscription.empty()) {
		cout << "no new subscribtion available" << endl;
		return false;
	}
	do {
		cout << "enter subscription name : ";
		cin >> subName;

		for (i = 0; i < newSubscription.size(); i++) {
			if (newSubscription[i].name == subName) {
				cout << "subscription name : " << newSubscription[i].name << endl;
				cout << "Duration : " << newSubscription[i].duration << " months" << endl;
				cout << "number of trips : " << newSubscription[i].newTrips << endl;
				cout << "Fee : " << newSubscription[i].fee << " LE " << endl;
				cout << "Enter Y to Confirm OR Enter N to Decline : ";
				cin >> choice;
				if (choice == "y" || choice == "Y") {
					found = true;
					break;
				}
			}
		}
	} while (found != true && subName != "exit");

	if (found) {
		subscriptionName = newSubscription[i].name;
		numberOfTrips = newSubscription[i].newTrips;
		startDate = std::chrono::system_clock::now();
		endtDate = startDate + std::chrono::hours(24 * 30 * newSubscription[i].duration);
		return true;
	}
	else
		return false;
}
void Subscription::ChangeBalanceLimit() {
	int newLimit;
	cout << "enter new balance limit : ";
	cin >> newLimit;
	balanceLimit = newLimit;

	cout << "new limit = " << balanceLimit << endl;
}
void Subscription::SubscriptionManagement() {
	int choice;
	int type;
	do {
		cout << "1.create new plan " << endl;
		cout << "2.delete subscription plan" << endl;
		cout << "3.Modify plan" << endl;
		cout << "4.Exit" << endl;
		cin >> choice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		if (choice == 1) {
			AddNewSubscription();
		}
		else if (choice == 2) {
			RemoveSubscriptionPLan();
		}
		else if (choice == 3) {
			cout << "1.modify price" << endl;
			cout << "2.modify duration" << endl;
			cout << "3.modify number of trips" << endl;
			cout << "4.modify balance limit" << endl;
			cin >> type;
			switch (type) {
			case 1:
				UpdateStagePrice();
				break;
			case 2:
				ChangeDuration();
				break;
			case 3:
				ChangeNumberOFTrips();
				break;
			case 4:
				ChangeBalanceLimit();
			default:
				cout << "invalid input " << endl;
				break;
			}
		}
		
		else
			cout << "invalid input " << endl;

	} while (choice != 4);
}
Subscription::Subscription(int trips, double money, string type, string start, string end, int stages)
{
	numberOfTrips = trips;
	balance = money;
	subscriptiontype = getType(type);
	stage_number = stages;
	startDate = stringToTimePoint(start);
	endtDate = stringToTimePoint(end);

}