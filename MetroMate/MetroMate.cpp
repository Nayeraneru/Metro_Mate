#include<iostream>
#include<fstream>
#include<chrono>
#include<sstream>
#include<map>
#include<list>
#include"Metro.h"
#include"Station.h"
#include "Train.h"
#include "Admin.h"
#include"user.h"
#include<regex>
 double stage1_fare = 6.0;
 double stage2_fare = 8.0;
 double stage3_fare = 12.0;
 double stage4_fare = 15.0;

using namespace std;
Metro metro;
list<user*> users;
user* currentUser;
Admin admin;
Ride ride;
bool is_valid_email(string email) {
	if (email.find('@') != string::npos) {
		//until the end of the string.
		size_t pos = email.find('@');
		string beforePart = email.substr(0, pos);
		string afterPart = email.substr(pos + 1);

		if (!beforePart.empty() && regex_match(beforePart, std::regex(".*[a-zA-Z].*")) && afterPart == "gmail.com") {
			return true;
		}
	}
	return false;
}
bool is_valid_password(string password) {
	return password.length() >= 8;
}
bool is_username_exist(string new_username) {
	for (user* user : users) {
		if (user->get_username() == new_username) {
			return false;
		}
	}
	return true;
}
bool is_email_exist(string new_email) {
	for (user* user : users) {
		if (user->get_email() == new_email) {
			return false;
		}
	}
	return true;
}
void users_registration() {

	bool is_exist;
	string username,email,password;
	do {
		cout << "Enter your username please: " << endl;
		cin >> username;
		is_exist = is_username_exist(username);
		if (!is_exist) {
			cout << "The username you've entered already exists, please choose another username" << endl;
		}
	} while (!is_exist);

	do {

		cout << "Enter your email please :" << endl;
		do {

			cin >> email;
			if (!is_valid_email(email)) {
				cout << "Email is not valid. please enter a valid email.";
			}
		} while (!is_valid_email(email));

		is_exist = is_email_exist(email);
		if (!is_exist) {
			cout << "The email you've entered already exists, please choose another email" << endl;
		}
	} while (!is_exist);

	do {
		cout << "Please enter your password :" << endl;
		cin >> password;
		if (!is_valid_password(password)) {
			cout << "Password isn't valid, please enter a valid password (at least 8 characters)" << endl;
		}
	} while (!is_valid_password(password));
	user* newUser=new user(username, email, password);
	users.push_back(newUser);
}
void readStations() {
	ifstream f;
	f.open("Stations.txt");
	if (!f) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	string line;
	while (getline(f, line)) {
		if (line==";") {
			break;
		}
		stringstream ss(line);
	
		string stationName, line1, line2, line3;
		bool bline1, bline2, bline3;
		getline(ss, stationName, ',');
		getline(ss, line1, ',');
		getline(ss, line2, ',');
		getline(ss, line3, ',');
		
		if (line1 == "true") {
			bline1 = true;
		}
		else
		{
			bline1 = false;
		}
		if (line2 == "true") {
			bline2 = true;
		}
		else
		{
			bline2 = false;
		}
		if (line3 == "true") {
			bline3 = true;
		}
		else
		{
			bline3 = false;
		}
		metro.addStation(stationName, bline1, bline2, bline3);
		string lined;
		while (getline(f, lined)) {
			if (lined == "-") {
				break;
			}
			stringstream sm(lined);
			string num1, num2, date;
			getline(sm, date, ',');
			getline(sm, num1, ',');
			getline(sm, num2, ',');

			metro.mapGraph[stationName].first.addData(date, stoi(num1), stod(num2));

		}

	}
	string lines;
	while (getline(f, lines)) {
		stringstream ss(lines);
		string firstStation, secondStation;
		getline(ss, firstStation, ',');
		getline(ss, secondStation, ',');
		
	metro.insertAt(firstStation, secondStation);
		
	}
	f.close();
}
void writeStations() {
	ofstream f;
	f.open("Stations.txt");
	if (!f) {
		cerr << "Error opening file for writing." << endl;
		return;
	}
	metro.writeFile(&f);
	f.close();

}
void readUsers(ifstream* f) {
	string line;
	while (getline(*f, line)) {
		stringstream ss(line);
		string Name, mail, passWord,points;
		getline(ss, Name, ',');
		getline(ss, mail, ',');
		getline(ss, passWord, ',');
		getline(ss, points, ',');
		getline(*f, line);
		stringstream sd(line);

		string trips, stages, money, type, start, end;
		getline(sd, trips, ',');
		getline(sd, money, ',');
		getline(sd, type, ',');
		getline(sd, stages, ',');
		getline(sd, start, ',');
		getline(sd, end, ',');

	

		user* newUser=new user( Name, mail, passWord,stoi(points), stoi(trips), stod(money), type, start, end, stoi(stages));
		string lines;
		while (true) {
			getline(*f, lines);
			if (lines == "&") {
				break;
			}
			
			stringstream sm(lines);

			string start_station, end_station, date;
			getline(sm, start_station, ',');
			getline(sm, end_station, ',');
			getline(sm, date, ',');
		
			Ride ride(start_station, end_station, date);
			newUser->user_rides.push_back(ride);
		
		}
		string line1;
		while (true) {
			getline(*f, line1);
			if (line1 == ";") {
				break;
			}

			stringstream sm(line1);

			string question;
			getline(sm, question);
			newUser->questionStack.push(question);

		}
		
		
		users.push_back(newUser);
	}

}
void writeUsers(ofstream* f)
{
	for (auto it = users.begin(); it != users.end(); it++) {

		(*it)->writeUsers((*it), f);
	}

}
void writeAllFiles() {
	writeStations();
	ofstream f;
	f.open("Users.txt");
	if (!f) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	writeUsers(&f);
	f.close(); 
	ofstream f1;
	f1.open("Subscription.txt");
	if (!f1) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	Subscription::writeNew(&f1);
	f1.close();
	ofstream f2;
	f2.open("Feedback.txt");
	if (!f2) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	admin.write(&f2);
	f2.close();
	ofstream f3;
	f3.open("Trains.txt");
	if (!f3) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	admin.writeTrians(&f3);
	f3.close();
}
void readAllFiles() {
	readStations();

	ifstream f;
	f.open("Users.txt");
	if (!f) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
readUsers(&f);
	f.close();
	ifstream f1;
	f1.open("Subscription.txt");
	if (!f1) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	Subscription::readWrite(&f1);
	f1.close();
	ifstream f2;
	f2.open("Feedback.txt");
	if (!f2) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	admin.read(&f2);
	f2.close();
	ifstream f3;
	f3.open("Trains.txt");
	if (!f3) {
		cerr << "Error opening file for reading." << endl;
		return;
	}
	admin.readTrains(&f3);
	f3.close();
}
void addGraph() {
	//readStations();
	
	metro.addStation("adly mansour", false,false,true);
	metro.addStation("haikstep", false, false, true);
	metro.addStation("omar bn el khatab", false, false, true);
	metro.addStation("qebaa", false, false, true);
	metro.addStation("hesham barakat", false, false, true);
	metro.addStation("nozha", false, false, true);
	metro.addStation("el shams club", false, false, true);
	metro.addStation("alf maskan", false, false, true);
	metro.addStation("helioplois", false, false, true);
	metro.addStation("haroun", false, false, true);
	metro.addStation("al ahram", false, false, true);
	metro.addStation("kolleyet el banat", false, false, true);
	metro.addStation("stadium", false, false, true);
	metro.addStation("fair zone", false, false, true);
	metro.addStation("abbasya", false, false, true);
	metro.addStation("abdou basha", false, false, true);
	metro.addStation("el geish", false, false, true);
	metro.addStation("bab el shaareya", false, false, true);
	metro.addStation("attaba", false, true, true);
	metro.addStation("nasser", true, false, true);
	metro.addStation("maspero", false, false, true);
	metro.addStation("safaa hegazy", false, false, true);
	metro.addStation("kit kat", false, false, true);
	metro.addStation("tawfikia", false, false, true);
	metro.addStation("wadi el nile", false, false, true);
	metro.addStation("gamaet el dowel", false, false, true);
	metro.addStation("boulak el dakrour", false, false, true);
	metro.addStation("el sudan", false, false, true);
	metro.addStation("imbaba", false, false, true);
	
	//line three conncetions
	metro.insertAt("haikstep", "adly mansour");
	metro.insertAt("omar bn el khatab", "haikstep");
	metro.insertAt("qebaa", "omar bn el khatab");
	metro.insertAt("hesham barakat", "qebaa");
	metro.insertAt("nozha", "hesham barakat");
	metro.insertAt("el shams club", "nozha");
	metro.insertAt("alf maskan", "el shams club");
	metro.insertAt("helioplois", "alf maskan");
	metro.insertAt("haroun", "helioplois");
	metro.insertAt("al ahram", "haroun");
	metro.insertAt("kolleyet el banat", "al ahram");
	metro.insertAt("stadium", "kolleyet el banat");
	metro.insertAt("fair zone", "stadium");
	metro.insertAt("abbasya", "fair zone");
	metro.insertAt("abdou basha", "abbasya");
	metro.insertAt("el geish", "abdou basha");
	metro.insertAt("bab el shaareya", "el geish");
	metro.insertAt("attaba", "bab el shaareya");
	metro.insertAt("nasser", "attaba");
	metro.insertAt("maspero", "nasser");
	metro.insertAt("safaa hegazy", "maspero");
	metro.insertAt("kit kat", "safaa hegazy");
	metro.insertAt("tawfikia", "kit kat");
	metro.insertAt("wadi el nile", "tawfikia");
	metro.insertAt("gamaet el dowel", "wadi el nile");
	metro.insertAt("boulak el dakrour", "gamaet el dowel");
	metro.insertAt("kit kat", "el sudan");
	metro.insertAt("imbaba", "el sudan");

	//line two
	metro.addStation("shubra el kheima", false, true, false);
	metro.addStation("koleyet el zeraa", false, true, false);
	metro.addStation("el mezalat", false, true, false);
	metro.addStation("el khalafawy", false, true, false);
	metro.addStation("saint theresa", false, true, false);
	metro.addStation("rod el farag", false, true, false);
	metro.addStation("massara", false, true, false);
	metro.addStation("al shohadaa", true, true, false);
	metro.addStation("nageeb", false, true, false);
	metro.addStation("el sadat", true, true, false);
	metro.addStation("opera", false, true, false);
	metro.addStation("dokki", false, true, false);
	metro.addStation("el bohoos", false, true, false);
	metro.addStation("cairo university", false, true, true);
	metro.addStation("faysal", false, true, false);
	metro.addStation("giza", false, true, false);
	metro.addStation("om el masryeen", false, true, false);
	metro.addStation("sakeyt mekky", false, true, false);
	metro.addStation("el moneeb", false, true, false);
	// line two connections
	metro.insertAt("koleyet el zeraa", "shubra el kheima");
	metro.insertAt("el mezalat", "koleyet el zeraa");
	metro.insertAt("el khalafawy", "el mezalat");
	metro.insertAt("saint theresa", "el khalafawy");
	metro.insertAt("rod el farag", "saint theresa");
	metro.insertAt("massara", "rod el farag");
	metro.insertAt("al shohadaa", "massara");
	metro.insertAt("attaba", "al shohadaa");
	metro.insertAt("nageeb", "attaba");
	metro.insertAt("el sadat", "nageeb");
	metro.insertAt("opera", "el sadat");
	metro.insertAt("dokki", "opera");
	metro.insertAt("el bohoos", "dokki");
	metro.insertAt("cairo university", "el bohoos");
	metro.insertAt("faysal", "cairo university");
	metro.insertAt("boulak el dakrour", "cairo university");
	metro.insertAt("giza", "faysal");
	metro.insertAt("om el masryeen", "giza");
	metro.insertAt("el moneeb", "om el masryeen");

	//line one
	metro.addStation("new el marg", true, false, false);
	metro.addStation("el marg", true, false, false);
	metro.addStation("ezbet el nakhl", true, false, false);
	metro.addStation("ain shams", true, false, false);
	metro.addStation("mattareya", true, false, false);
	metro.addStation("helmeyet el zaytoun", true, false, false);
	metro.addStation("hadayek el zaytoun", true, false, false);
	metro.addStation("saray el qubba", true, false, false);
	metro.addStation("hammamat el qubba", true, false, false);
	metro.addStation("kobry el qubaa", true, false, false);
	metro.addStation("manshyet el sadr", true, false, false);
	metro.addStation("el demerdash", true, false, false);
	metro.addStation("ghamra", true, false, false);
	metro.addStation("orabi", true, false, false);
	metro.addStation("saad zaghloul", true, false, false);
	metro.addStation("sayeda zainab", true, false, false);
	metro.addStation("el malek el saleh", true, false, false);
	metro.addStation("mar girgis", true, false, false);
	metro.addStation("dar el salam", true, false, false);
	metro.addStation("hadayek el maadi", true, false, false);
	metro.addStation("el maadi", true, false, false);
	metro.addStation("sakanat el maadi", true, false, false);
	metro.addStation("tura el balad", true, false, false);
	metro.addStation("kozzika", true, false, false);
	metro.addStation("tura el asmant", true, false, false);
	metro.addStation("el maasara", true, false, false);
	metro.addStation("hadayek helwan", true, false, false);
	metro.addStation("wadi hof", true, false, false);
	metro.addStation("helwan university", true, false, false);
	metro.addStation("ain helwan", true, false, false);
	metro.addStation("helwan", true, false, false);
	//line one connections
	metro.insertAt("el marg", "new el marg");
	metro.insertAt("ezbet el nakhl", "el marg");
	metro.insertAt("ain shams", "ezbet el nakhl");
	metro.insertAt("mattareya", "ain shams");
	metro.insertAt("helmeyet el zaytoun", "mattareya");
	metro.insertAt("hadayek el zaytoun", "helmeyet el zaytoun");
	metro.insertAt("saray el qubba", "hadayek el zaytoun");
	metro.insertAt("hammamat el qubba", "saray el qubba");
	metro.insertAt("kobry el qubaa", "hammamat el qubba");
	metro.insertAt("manshyet el sadr", "kobry el qubaa");
	metro.insertAt("el demerdash", "manshyet el sadr");
	metro.insertAt("ghamra", "el demerdash");
	metro.insertAt("al shohadaa", "ghamra");
	metro.insertAt("orabi", "al shohadaa");
	metro.insertAt("nasser", "orabi");
	metro.insertAt("el sadat", "nasser");
	metro.insertAt("saad zaghloul", "el sadat");
	metro.insertAt("sayeda zainab", "saad zaghloul");
	metro.insertAt("el malek el saleh", "sayeda zainab");
	metro.insertAt("mar girgis", "el malek el saleh");
	metro.insertAt("dar el salam", "mar girgis");
	metro.insertAt("hadayek el maadi", "dar el salam");
	metro.insertAt("el maadi", "hadayek el maadi");
	metro.insertAt("sakanat el maadi", "el maadi");
	metro.insertAt("tura el balad", "sakanat el maadi");
	metro.insertAt("kozzika", "tura el balad");
	metro.insertAt("tura el asmant", "kozzika");
	metro.insertAt("el maasara", "tura el asmant");
	metro.insertAt("hadayek helwan", "el maasara");
	metro.insertAt("wadi hof", "hadayek helwan");
	metro.insertAt("helwan university", "wadi hof");
	metro.insertAt("ain helwan", "helwan university");
	metro.insertAt("helwan", "ain helwan");

}
std::string timePointToString(const std::chrono::system_clock::time_point& tp)
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
void bookRide() {
	if (currentUser->subscription.ConvertToString() == "No subscription found") {
		cout << "You don't have a method to pay yet, Please choose a method first\n";
		return;
	}
	if (currentUser->subscription.ConvertToString() != "CASH" && currentUser->subscription.getNumberOfTrips() == 0) {
		cout << "You don't have anymore rides.\n";
		return;

	}
	string s = currentUser->suggestRide();
	string from, to;
	int choice;
	if (s != "false") {
		string delimiter = "-";
		string first = s.substr(0, s.find(delimiter));
		string second = s.substr((s.find(delimiter) + 1), s.size());
		cout << "Suggested Ride!!\n";
		cout << "Go from " << first << " to " << second << endl;
		cout << "Please enter your choice:\n";
		while (true) {
			cout << "1) Book the suggested ride.\n";
			cout << "2) Choose another ride.\n";
			cin >> choice;
			if (cin.fail()) {
				cout << "Invalid, Please try again.\n" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (choice == 1) {
				int fare = metro.getPath(first, second);
				if (currentUser->subscription.ConvertToString() == "NEW") {
					Ride ride(first, second);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[first + '-' + second]++;
					currentUser->subscription.numberOfTrips--;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[first].first.addData(time, tickets, 0.0);

				}
				else if (currentUser->subscription.ConvertToString() != "CASH") {
					if (currentUser->subscription.getStageNumber() == 1) {
						if (fare - 1 <= 9) {
							Ride ride(first, second);

							currentUser->user_rides.push_back(ride);
							currentUser->frequent_rides[first + '-' + second]++;
							currentUser->subscription.numberOfTrips--;
							string time = timePointToString(std::chrono::system_clock::now());
							int tickets = ++Station::numberOfTickets;
							metro.mapGraph[first].first.addData(time, tickets, 0.0);
						}
						else {
							cout << "Please choose another ride with suitible stations.\n";
						}
					}
					else if (currentUser->subscription.stage_number == 2) {
						if (fare - 1 <= 16) {
							Ride ride(first, second);
							currentUser->user_rides.push_back(ride);
							currentUser->frequent_rides[first + '-' + second]++;
							currentUser->subscription.numberOfTrips--;
							string time = timePointToString(std::chrono::system_clock::now());
							int tickets = ++Station::numberOfTickets;
							metro.mapGraph[first].first.addData(time, tickets, 0.0);
						}
						else {
							cout << "Please choose another ride with suitible stations.\n";
						}
					}
					else if (currentUser->subscription.stage_number == 3) {
						if (fare - 1 <= 23) {
							Ride ride(first, second);
							currentUser->user_rides.push_back(ride);
							currentUser->frequent_rides[first + '-' + second]++;
							currentUser->subscription.numberOfTrips--;
							string time = timePointToString(std::chrono::system_clock::now());
							int tickets = ++Station::numberOfTickets;
							metro.mapGraph[first].first.addData(time, tickets, 0.0);
						}
						else {
							cout << "Please choose another ride with suitible stations.\n";
						}
					}
					else if (currentUser->subscription.stage_number == 4) {
						Ride ride(first, second);
						currentUser->user_rides.push_back(ride);
						currentUser->frequent_rides[first + '-' + second]++;
						currentUser->subscription.numberOfTrips--;
						string time = timePointToString(std::chrono::system_clock::now());
						int tickets = ++Station::numberOfTickets;
						metro.mapGraph[first].first.addData(time, tickets, 0.0);
					}
				}

				else {

					if (currentUser->myReward->check_reward()) {
						currentUser->myReward->redeem_reward();
						cout << "Fare: 0 LE" << endl;
					}
					else if (fare >= 0 && fare <= 9) {
						if (currentUser->subscription.balance - stage1_fare >= 0) {
							cout << "Fare: " << stage1_fare << " LE" << endl;
							Ride ride(first, second);
							currentUser->user_rides.push_back(ride);
							currentUser->frequent_rides[first + '-' + second]++;
							currentUser->subscription.balance -= stage1_fare;
							string time = timePointToString(std::chrono::system_clock::now());
							int tickets = ++Station::numberOfTickets;
							metro.mapGraph[first].first.addData(time, tickets, stage1_fare);
							cout << "Your current balance is: " << currentUser->subscription.balance << endl;
							currentUser->myReward->increment_points();
						}
						else {
							cout << "You don't have enough balance.\n";
						}
					}
					else if (fare <= 16) {
						if (currentUser->subscription.balance - stage2_fare >= 0) {
							cout << "Fare: " << stage2_fare << " LE" << endl;
							Ride ride(first, second);
							currentUser->user_rides.push_back(ride);
							currentUser->frequent_rides[first + '-' + second]++;
							currentUser->subscription.balance -= stage2_fare;
							string time = timePointToString(std::chrono::system_clock::now());
							int tickets = ++Station::numberOfTickets;
							metro.mapGraph[first].first.addData(time, tickets, stage2_fare);
							cout << "Your current balance is: " << currentUser->subscription.balance << endl;
							currentUser->myReward->increment_points();
						}
						else {
							cout << "You don't have enough balance.\n";
						}
					}
					else if (fare <= 23) {
						if (currentUser->subscription.balance - stage3_fare >= 0) {
							cout << "Fare: " << stage3_fare << " LE" << endl;
							Ride ride(first, second);
							currentUser->user_rides.push_back(ride);
							currentUser->frequent_rides[first + '-' + second]++;
							currentUser->subscription.balance -= stage3_fare;
							string time = timePointToString(std::chrono::system_clock::now());
							int tickets = ++Station::numberOfTickets;
							metro.mapGraph[first].first.addData(time, tickets, stage3_fare);
							cout << "Your current balance is: " << currentUser->subscription.balance << endl;
							currentUser->myReward->increment_points();
						}
						else {
							cout << "You don't have enough balance.\n";
						}
					}
					else if (fare > 23) {
						if (currentUser->subscription.balance - stage4_fare >= 0) {
							cout << "Fare: " << stage4_fare << " LE" << endl;
							Ride ride(first, second);
							currentUser->user_rides.push_back(ride);
							currentUser->frequent_rides[first + '-' + second]++;
							currentUser->subscription.balance -= stage4_fare;
							string time = timePointToString(std::chrono::system_clock::now());
							int tickets = ++Station::numberOfTickets;
							metro.mapGraph[first].first.addData(time, tickets, stage4_fare);
							cout << "Your current balance is: " << currentUser->subscription.balance << endl;
							currentUser->myReward->increment_points();
						}
						else {
							cout << "You don't have enough balance.\n";
						}
					}
					else
						cout << "Invalid number of stations traveled." << endl;
				}


				return;
			}
			else if (choice == 2) {
				break;
			}
			else {
				cout << "Please enter a valid choice.\n";
			}
		}
	}

	if (s == "false" || choice == 2) {
		cout << "Please enter your station:\n";

		while (true) {
			cin.ignore();
			getline(cin, from);
		
			if (metro.mapGraph.find(from) != metro.mapGraph.end()) {
			
				break;
			}
			cout << "Please enter a valid station name:\n";
		
		}
		cout << "Please enter your destination:\n";
		while (true) {
			
			getline(cin, to);
		
		
			if (metro.mapGraph.find(to) != metro.mapGraph.end()) {	
				break;
			}
	cout << "Please enter a valid station name:\n";
		}
		int fare = metro.getPath(from, to);
		if (currentUser->subscription.ConvertToString() == "NEW") {
			Ride ride(from, to);
			currentUser->user_rides.push_back(ride);
			currentUser->frequent_rides[from + '-' + to]++;
			currentUser->subscription.numberOfTrips--;
			string time = timePointToString(std::chrono::system_clock::now());
			int tickets = ++Station::numberOfTickets;
			metro.mapGraph[from].first.addData(time, tickets, 0.0);
		}
		else if (currentUser->subscription.ConvertToString() != "CASH") {
			if (currentUser->subscription.getStageNumber() == 1) {
				if (fare - 1 <= 9) {
					Ride ride(from, to);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[from + '-' + to]++;
					currentUser->subscription.numberOfTrips--;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[from].first.addData(time, tickets, 0.0);
				}
				else {
					cout << "Please choose another ride with suitible stations.\n";
				}
			}
			else if (currentUser->subscription.getStageNumber() == 2) {
				if (fare - 1 <= 16) {
					Ride ride(from, to);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[from + '-' + to]++;
					currentUser->subscription.numberOfTrips--;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[from].first.addData(time, tickets, 0.0);
				}
				else {
					cout << "Please choose another ride with suitible stations.\n";
				}
			}
			else if (currentUser->subscription.getStageNumber() == 3) {
				if (fare - 1 <= 23) {
					Ride ride(from, to);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[from + '-' + to]++;
					currentUser->subscription.numberOfTrips--;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[from].first.addData(time, tickets, 0.0);
				}
				else {
					cout << "Please choose another ride with suitible stations.\n";
				}
			}
			else if (currentUser->subscription.getStageNumber() == 4) {
				Ride ride(from, to);
				currentUser->user_rides.push_back(ride);
				currentUser->frequent_rides[from + '-' + to]++;
				currentUser->subscription.numberOfTrips--;
				string time = timePointToString(std::chrono::system_clock::now());
				int tickets = ++Station::numberOfTickets;
				metro.mapGraph[from].first.addData(time, tickets, 0.0);
			}
		}

		else {

			if (currentUser->myReward->check_reward()) {
				currentUser->myReward->redeem_reward();
				cout << "Fare: 0 LE" << endl;
			}
			else if (fare >= 0 && fare <= 9) {

				if (currentUser->subscription.balance - stage1_fare >= 0) {
					cout << "Fare: " << stage1_fare << " LE" << endl;
					Ride ride(from, to);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[from + '-' + to]++;
					currentUser->subscription.balance -= stage1_fare;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[from].first.addData(time, tickets, stage1_fare);
					cout << "Your current balance is: " << currentUser->subscription.balance << endl;
					currentUser->myReward->increment_points();
				}
				else {
					cout << "You don't have enough balance.\n";
				}
			}
			else if (fare <= 16) {
				if (currentUser->subscription.balance - stage2_fare >= 0) {
					Ride ride(from, to);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[from + '-' + to]++;
					cout << "Fare: " << stage2_fare << " LE" << endl;
					currentUser->subscription.balance -= stage2_fare;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[from].first.addData(time, tickets, stage2_fare);
					cout << "Your current balance is: " << currentUser->subscription.balance << endl;
					currentUser->myReward->increment_points();
				}
				else {
					cout << "You don't have enough balance.\n";
				}
			}
			else if (fare <= 23) {
				if (currentUser->subscription.balance - stage3_fare >= 0) {
					Ride ride(from, to);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[from + '-' + to]++;
					cout << "Fare: " << stage3_fare << " LE" << endl;
					currentUser->subscription.balance -= stage3_fare;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[from].first.addData(time, tickets, stage3_fare);
					cout << "Your current balance is: " << currentUser->subscription.balance << endl;
					currentUser->myReward->increment_points();
				}
				else {
					cout << "You don't have enough balance.\n";
				}
			}
			else if (fare > 23) {
				if (currentUser->subscription.balance - stage4_fare >= 0) {
					Ride ride(from, to);
					currentUser->user_rides.push_back(ride);
					currentUser->frequent_rides[from + '-' + to]++;
					cout << "Fare: " << stage4_fare << " LE" << endl;
					currentUser->subscription.balance -= stage4_fare;
					string time = timePointToString(std::chrono::system_clock::now());
					int tickets = ++Station::numberOfTickets;
					metro.mapGraph[from].first.addData(time, tickets, stage4_fare);
					cout << "Your current balance is: " << currentUser->subscription.balance << endl;
					currentUser->myReward->increment_points();
				}
				else {
					cout << "You don't have enough balance.\n";
				}
			}
			else
				cout << "Invalid number of stations traveled." << endl;


		}
	}

}
void editInfo() {
	cout << "Your info:\n";
	cout << "Your Username: " << currentUser->get_username();
	cout << "\nYour Email: " << currentUser->get_email() << endl;
	cout << "Please enter your choice:\n";
	while (true) {
		cout << "1) Change my email\n";
		cout << "2) Change my username\n";
		cout << "3) Change my password\n";
		cout << "4) Go back\n";
		int editChoice;
		cin >> editChoice;

		if (cin.fail()) {
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (editChoice == 1) {
			currentUser->changeEmail();
		}
		else if (editChoice == 2) {
			currentUser->changeUsername();
		}
		else if (editChoice == 3) {
			currentUser->changePassword();
		}
		else if (editChoice == 4) {
			return;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}
void mainMenu() {
	cout << "------------------------- Welcome to MetroMate!! -----------------------------" << endl;
	while (true) {
		cout << "Please enter your choice:" << endl;
		cout << "1) Book a ride:" << endl;
		cout << "2) Manage subscribtions:" << endl;
		cout << "3) View rides history:" << endl;
		cout << "4) Edit your personal information:" << endl;
		cout << "5) customer service: " << endl;
		cout << "6) Log out:" << endl;
		int  menuChoice;
		cin >> menuChoice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (menuChoice == 1) {
			bookRide();
		}
		else if (menuChoice == 2) {
			currentUser->subscription.SubscriptionMenu();
		}
		else if (menuChoice == 3) {
			currentUser->display_ride_history();
		}
		else if (menuChoice == 4) {
			editInfo();
		}
		else if (menuChoice == 5)
		{
			currentUser->customerService(&admin.SupportRespones);

		}
		else if (menuChoice == 6)
		{
			return;
		}
		else {
			cout << "Invalid, Please try again." << endl;
		}

	}

}
void userManagement() {
	int userChoice;
	string username;

	cout << "User Management:" << endl;
	cout << "Enter the username of the user you want to manage: ";
	cin >> username;

	bool found = false;
	for (auto it = users.begin(); it != users.end(); ++it) {
		if ((*it)->get_username() == username) {
			currentUser = *it;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "User not found." << endl;
		return;
	}

	cout << "Choose an option:" << endl;
	cout << "1. Change username" << endl;
	cout << "2. Change email" << endl;
	cout << "3. Change password" << endl;
	cout << "4. delete user" << endl;
	cout << "5. Back to main menu" << endl;
	cout << "Enter your choice: ";
	cin >> userChoice;

	switch (userChoice) {
	case 1: {
		string newUsername;
		cout << "Enter new username: ";
		cin >> newUsername;
		currentUser->set_username(newUsername);
		cout << "Username changed successfully!" << endl;
		break;
	}
	case 2: {
		string newEmail;
		cout << "Enter new email: ";
		cin >> newEmail;
		currentUser->set_email(newEmail);
		cout << "Email changed successfully!" << endl;
		break;
	}
	case 3: {
		string newPassword;
		cout << "Enter new password: ";
		cin >> newPassword;
		currentUser->set_password(newPassword);
		cout << "Password changed successfully!" << endl;
		break;
	}
	case 4: {
		delete currentUser;
		users.remove(currentUser);
		cout << "User removed successfully." << endl;
		break;
	}
	case 5:
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
	}
}
void AdminMenu() {

	cout << "-------------------- Admin Menu --------------------" << endl;
	cout << endl;
	int choice;
	bool exitMenu = false;
Subscription sub;
	do {

		cout << "Enter your choice: ";
		cout << endl;
		cout << "1. User Management\n";
		cout << "2. Metro Management\n";
		cout << "3. Subscription Plan Management\n";
		cout << "4. View All Ride Logs\n";
		cout << "5. Station Management\n";
		cout << "6. Fare Management\n";
		cout << "7. Train Management\n";
		cout << "8. Display Reviews\n";
		cout << "9. Exit\n";

		cin >> choice;

		switch (choice) {
		case 1:
			userManagement();
			break;
		case 2:
			admin.MetroManagement();
			break;
		case 3: 
			sub.SubscriptionManagement();
			break;
		case 4:
			for (auto it = users.begin(); it != users.end(); it++) {
				cout << "-------------------------";
				cout << "name: " << (*it)->get_username() << endl;
				(*it)->display_ride_history();
			}
			cout << "-------------------------";
			break;
		case 5:
			admin.StationManagement();
			break;
		case 6:
			admin.FareManagement(stage1_fare, stage2_fare, stage3_fare, stage4_fare);
			break;

		case 7:
			admin.TrainManagement(&metro);
			break;

		case 8:
			admin.CustomerServiceMenu(currentUser->questionStack);
			admin.SendReplies();
			break;
		case 9:
			exitMenu = true;
			break;
		default:
			cout << "Invalid choice ,Please try again.\n";
		}


	} while (!exitMenu);
}
void login() {
	string username, password_entered;
	while (true) {
		cout << "Enter your username please:\n";
		cin >> username;
		cout << "Enter your password please:\n";
		cin >> password_entered;
		if (username == "farah" && password_entered == "farahfarah") {
			AdminMenu();
			break;
		}
		else {
			for (auto it=users.begin();it!=users.end();it++) {
				if ((*it)->get_username() == username && (*it)->get_password() == password_entered) {
					currentUser = *it;
					mainMenu();
					return;
				}
			
			}
			cout << "please enter a valid username and password\n";
		}
	}
}
int main(){
	//ÊÍæíáÇÊ:
	//"Nageeb", "Maspero" 
	//"Massara", "Nasser"
	//"Ghamra", "Nasser"
	admin.metro = &metro;
	readAllFiles();
	while (true) {
		cout << "Please choose:\n";
		cout << "1) Register.\n";
		cout << "2) Login.\n";
		cout << "3) Exit.\n";
		int  menuChoice;
		cin >> menuChoice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (menuChoice == 1) {
			users_registration();
		}
		else if (menuChoice == 2) {
			login();
		}
		else if (menuChoice == 3) {
			break;
		}
		else{
			cout << "Invalid, Please try again." << endl;
		}
		
	}
	writeAllFiles();
	return 0;
}

