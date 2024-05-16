#include<chrono>
#include<iostream>
#include<cctype>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;

enum class SubscriptionType {
	STUDENT,
	PUBLIC_MONTH,
	PUBLIC_YEAR,
	CASH,
	NEW,
	NONE
};

class Subscription {
public:
	

	struct NewSubscription {
		string name;
		int duration;
		int fee;
		int newTrips;
		NewSubscription() {
			name = "";
			duration = 0;
			fee = 0;
			newTrips = 0;
		}
		NewSubscription(string Name,int Duration,int fees,int newtrips) {
			name = Name;
			duration = Duration;
			fee = fees;
			newTrips = newtrips;
		}
		string newToString()
		{

			return name + "," + to_string(duration) + "," + to_string(fee) + "," + to_string(newTrips);
		}
	};

	string subscriptionName;

	static vector<NewSubscription> newSubscription;
	string toString();
	int numberOfTrips;
	double balance;
	SubscriptionType subscriptiontype;
	std::chrono::system_clock::time_point startDate;
	std::chrono::system_clock::time_point endtDate;

	int stage_number;

	int balanceLimit = 400;

	static int stage1_fee_student ;
	static int stage2_fee_student ;
	static int stage3_fee_student ;
	static int stage4_fee_student ;

	static int stage1_fee_public_month ;
	static int stage2_fee_public_month ;
	static int stage3_fee_public_month ;
	static int stage4_fee_public_month ;

	static int stage1_fee_public_year ;
	static int stage2_fee_public_year ;
	static int stage3_fee_public_year ;
	static int stage4_fee_public_year ;

	bool studentFlag = true;
	bool publicMonthFlag = true;
	bool publicYearFlag = true;
	bool cashFlag = true;

	int studentTrips = 180;
	int publicMonthTrips = 60;
	int publicYearTrips = 730;

	int studentDuration = 3;
	int publicMonthDuration = 1;
	int  publicYearDuration = 12;


	Subscription();
	void ChooseSubscription();
	void DisplaySubscriptionDetail();
	int CalculateNumberOfDaysRemaining();
	void RenewSubscription();
	void UpgradeSubscription();
	void SubscriptionMenu();
	void Addbalance();
	string ConvertToString(SubscriptionType type);
	string ConvertToString();
	SubscriptionType getType(string type);
	static void writeNew(ofstream* f);
	static void readWrite(ifstream* f);
	double getBalance();
	int getNumberOfTrips();
	int getStageNumber();
	void UpdateStagePrice();
	void RemoveSubscriptionPLan();
	void ChangeNumberOFTrips();
	void ChangeDuration();
	void AddNewSubscription();
	void DisplyNewSubscription();
	bool ChooseNewSubscription();
	void SubscriptionManagement();
	void ChangeBalanceLimit();
	Subscription(int trips, double money, string type, string start, string end, int stages);
	std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTimeStr);
	std::string timePointToString(const std::chrono::system_clock::time_point& tp);

};