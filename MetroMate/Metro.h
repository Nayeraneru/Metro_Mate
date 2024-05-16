#pragma once
#include<vector>
#include<iostream>
#include"Station.h"
#include<map>
#include<fstream>

using namespace std;
class Metro
{

 map<string, bool> visited;
 bool flag;
public:
	
	map<string,pair<Station,vector <Station*>>> mapGraph;

	void addStation(string name, bool Line1, bool Line2, bool Line3);
	void addStation(string name, int lineNumber);
	void editStation(string name, string newName);
	void deleteStation(string name);
	void insertAt(string newStation, string atStation);
	int  getPath(string s,string d);
	void getAllPaths(string u, string d,  vector<string> path,vector<vector<string>>* allPaths);
	vector<Station*> getStationsForLine(int line);
	//Station& getStation(string name);
	void writeFile(ofstream* f);
       
};

