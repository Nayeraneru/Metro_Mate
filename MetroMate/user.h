#pragma once
#include <iostream>
#include <list>
#include <stack>
#include<map>
#include<fstream>
#include <queue>
#include<string>
#include"Subscription.h"
#include"Ride.h"
#include"RewardProgram.h"

using namespace std;

class user {
    string username;
    string email;
    string password;

public:
 
    list<Ride>user_rides;
    map<string,int>frequent_rides;
    stack<string>questionStack;
    void set_username(string);
    void set_password(string);
    void set_email(string);
    RewardProgram* myReward;
    Subscription subscription;
    void display_ride_history();
    user();
    user(string user_name, string user_email, string user_password);
    user(string new_user_name, string new_user_email, string new_user_password, int point,int trips, double money, string type, string start, string end, int stages);
   string suggestRide();

   bool is_valid_email(string Email);
   bool is_valid_password(string Password);
    void sendQuestion(string question);
    void changeUsername();
    stack<string> getQuestionStack();
    void getReply(queue<pair<string, string>>* replies);
    void customerService(queue<pair<string, string>>* replies);
   void changePassword();
    void changeEmail();
    //void deleteAccount(string username);
    //void viewUsers();
    //void editUser(string& Username);

    string get_username();
    string get_password();
    string get_email();
    string toString();
    void writeUsers(user* write, ofstream* f);


};