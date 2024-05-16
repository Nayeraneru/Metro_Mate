#include "Metro.h"
#include"Station.h"
#include<vector>

void Metro::insertAt(string NewStaion, string atStaion)
{
	mapGraph[atStaion].second.push_back(&(mapGraph[NewStaion].first));
}

void Metro::deleteStation(string name)
{

	// Delete connections
	for (int i = 0; i < mapGraph[name].second.size(); i++) {
		for (int j = i+1 ; j < mapGraph[name].second.size(); j++) {
			insertAt(mapGraph[name].second[i]->getName(), mapGraph[name].second[j]->getName());
		}
	}

	// Remove references to the station from other stations
	for (int i = 0; i < mapGraph[name].second.size(); i++) {
		for (int j = 0; j < mapGraph[mapGraph[name].second[i]->getName()].second.size(); j++) {
			if (mapGraph[mapGraph[name].second[i]->getName()].second[j]->getName() == name) {
				mapGraph[mapGraph[name].second[i]->getName()].second.erase(mapGraph[mapGraph[name].second[i]->getName()].second.begin() + j);
			}
		}
	}

	// Erase the station itself from the mapGraph
	mapGraph.erase(name);

	cout << "Station " << name << " was deleted successfully." << endl;
}

void Metro::addStation(string name, bool Line1,bool Line2,bool Line3)
{
	Station newStation(name, Line1,Line2,Line3);
	mapGraph[name].first= newStation;

	visited[name] = false;
	flag = false;
}
void Metro::addStation(string name, int lineNumber) {
	bool Line1 = false, Line2 = false, Line3 = false;

	switch (lineNumber) {
	case 1:
		Line1 = true;
		break;
	case 2:
		Line2 = true;
		break;
	case 3:
		Line3 = true;
		break;
	default:
		cout << "Invalid line number. Station will not be added to any line." << endl;
		return;
	}

	addStation(name, Line1, Line2, Line3);
}

void Metro::editStation(string name, string newName) {
	if (mapGraph.find(name) == mapGraph.end()) {
		cout << "Station with name " << name << " does not exist." << endl;
		return;
	}
	Station& station = mapGraph[name].first;
	station.stationName = newName;
	cout << "Station " << name << " renamed to " << newName << " successfully" << endl;
}
int Metro::getPath(string s,string d)
{
	
	vector<string> path;
	vector<vector<string>> allPaths;
	for (auto it = mapGraph.begin(); it !=mapGraph.end() ; it++)
		visited[it->first] = false;
	getAllPaths(s, d,  path,&allPaths);
	if (allPaths.size() == 1) {
		cout << allPaths[0][0];
		for (int i = 1; i < allPaths[0].size(); i++) {
			cout << "->" << allPaths[0][i];
		}
		cout << endl;
		return allPaths[0].size();
	}
	int min = 100000;
	int secondMin = 200000000;
	int index = -1;
	int secondIndex = -1;
	for (int i = 0; i < allPaths.size(); i++) {
		if (allPaths[i].size() <= min)
		{
			min = allPaths[i].size();
			index = i;
		}
		if (allPaths[i].size() <= secondMin && i!=index) {
			secondMin = allPaths[i].size();
			secondIndex = i;
		}
	} 
	int min_lines = 7;
	int secondMin_Lines = 7;
	for (int i = 0; i < allPaths.size(); i++) {
		if (allPaths[i].size() > min) {
			continue;
		}
		int count = 0;
		int secondCount = 0;
		for (int j = 1; j < allPaths[i].size()-1; j++) {
			if ((mapGraph[allPaths[i][j]].first.line1 && mapGraph[allPaths[i][j]].first.line2) || (mapGraph[allPaths[i][j]].first.line1 && mapGraph[allPaths[i][j]].first.line3) || (mapGraph[allPaths[i][j]].first.line2 && mapGraph[allPaths[i][j]].first.line3)) {
				count++;
				secondCount++;
			
}
		}
		if (count < min_lines) {
			min_lines = count;
			index = i;
		}
		if (secondCount<secondMin_Lines && i!=index) {
			secondMin_Lines = secondCount;
			secondIndex = i;
		}

	}
	cout << "youn may go to your destination by a couple of paths.\n";
	cout << "Path number 1(the shortest path):\n";
	cout << allPaths[index][0];
	for (int i = 1; i < allPaths[index].size(); i++) {
		cout << "->" << allPaths[index][i];
	}
	cout << "\n Path number 2(a longer one):\n";
	cout << allPaths[secondIndex][0];
	for (int i = 1; i < allPaths[secondIndex].size(); i++) {
		cout << "->" << allPaths[secondIndex][i];
	}
	cout << "\n Please enter your choise (1-2):";
	while (true) {
		int  choice;
		cin >> choice;
		if (cin.fail()) {
			cout << "Invalid, Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (choice == 1) {
			return allPaths[index].size();
		}
		else if (choice == 2) {
			return allPaths[secondIndex].size();
		}
		else {
			cout << "Invalid, please enter a number between 1-2:";
		}
	}
}

void Metro::getAllPaths(string u, string d, 
	vector<string> path,vector<vector<string>>* allPaths)
{
	visited[u] = true;
	path.push_back(u);
	if (u == d) {
		allPaths->push_back(path);
	}
	else
	{
		for (int i = 0; i < mapGraph[u].second.size(); i++)
			if (!visited[mapGraph[u].second[i]->getName()])
				getAllPaths(mapGraph[u].second[i]->getName(), d, path,allPaths);
	}
	visited[u] = false;
}
vector<Station*> Metro::getStationsForLine(int line) {
	vector<Station*> lineStations;
	for (auto it = mapGraph.begin(); it != mapGraph.end(); it++) {
		Station* station = &it->second.first;
		switch (line) {
		case 1:
			if (station->line1) {
				lineStations.push_back(station);
			}
			break;
		case 2:
			if (station->line2) {
				lineStations.push_back(station);
			}
			break;
		case 3:
			if (station->line3) {
				lineStations.push_back(station);
			}
			break;
		
		}
	}

	return lineStations;
}


void Metro::writeFile(ofstream* f)
{
	for (auto it = mapGraph.begin(); it != mapGraph.end(); it++) {
		(*f) << it->second.first.toString();
		(*f) << "\n";
			it->second.first.write(f);	
	}
	(*f) << ';'<<"\n";
	for (auto it = mapGraph.begin(); it != mapGraph.end(); it++) {
		for (int i = 0; i < it->second.second.size(); i++) {

			(*f) << it->first << "," << it->second.second[i]->getName() << "\n";

		}
	}
}
