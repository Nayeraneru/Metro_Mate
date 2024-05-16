#include "Admin.h"
#include<iostream>
using namespace std;

queue<pair<string, string>> SupportRespones;
void Admin::StationManagement() {
    int choice;
    string stationName;
    cout << "Write The Station Name :" << endl;
    cin.ignore();
        getline(cin, stationName);

    cout << "===============================" << endl;
    cout << "Choose :" << endl;
    cout << "===============================" << endl;
    cout << "1.Daily Income" << endl;
    cout << "2.Weekly Income" << endl;
    cout << "3.Monthly Income" << endl;
    cout << "4.Yearly Incom" << endl;
    cout << "===============================" << endl;
    cin >> choice;

    switch (choice) {

    case 1:
        metro->mapGraph[stationName].first.calculateDailyIncome();
        break;
    case 2:
        metro->mapGraph[stationName].first.calculateWeeklyIncome();
        break;

    case 3:
        metro->mapGraph[stationName].first.calculateMonthlyIncome();
        break;

    case 4:
        metro->mapGraph[stationName].first.calculateYearlyIncome();
        break;

    }
}
void Admin::write(ofstream* f)
{
        while (!SupportRespones.empty()) {
            (*f) << SupportRespones.front().first << "," << SupportRespones.front().second;
            SupportRespones.pop();
            (*f) << "\n";
        }
}
void Admin::read(ifstream* f) {
    string line;
    while (getline(*f, line)) {
        stringstream ss(line);
        string question, replay;
        getline(ss, question, ',');
        getline(ss, replay, ',');
        pair<string, string> newp;
        newp.first = question;
        newp.second = replay;
        SupportRespones.push(newp);
    }

}
void Admin::FareManagement(double& stage1_fare, double& stage2_fare, double& stage3_fare, double& stage4_fare) {

    int stageNumber;
    double newPrice;

    cout << "Enter the stage number :" << endl;
    cin >> stageNumber;

    cout << "Enter the new fare:" << endl;
    cin >> newPrice;


    switch (stageNumber) {
    case 1:
        stage1_fare = newPrice;
        break;
    case 2:
        stage2_fare = newPrice;
        break;
    case 3:
        stage3_fare = newPrice;
        break;
    case 4:
        stage4_fare = newPrice;
        break;
    default:
        cout << "Invalid stage number." << endl;
        return;
    }

    cout << "Fare updated successfully for stage " << stageNumber << endl;
}
void Admin::MetroManagement() {
    int choice;
    do {
        cout << "-------------------- Metro Management Menu --------------------" << endl;
        cout << "1. Add Metro Station" << endl;
        cout << "2. Edit Metro Station" << endl;
        cout << "3. Remove Metro Station" << endl;
        cout << "4. Back to Admin Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, connectedTo;
            int line;
            cout << "Enter the name of the metro station: ";
            cin >> name;
            cout << "Enter the line number it belongs to (1/2/3): ";
            cin >> line;
            bool line1 = false, line2 = false, line3 = false;
            if (line == 1) {
                line1 = true;
            }
            else if (line == 2) {
                line2 = true;
            }
            else if (line == 3) {
                line3 = true;
            }
            else {
                cout << "Invalid line number." << endl;
                break;
            }
            cout << "Enter the name of the metro station it's connected to: ";
            cin >> connectedTo;
            metro->addStation(name, line1, line2, line3);
            metro->insertAt(name, connectedTo);
            metro->insertAt(connectedTo, name);
            break;
        }
        case 2: {
            string name;
            int line;
            cout << "Enter the name of the metro station to edit: ";
            cin >> name;
            cout << "Enter the new line number for the station (1/2/3): ";
            cin >> line;
            bool line1 = false, line2 = false, line3 = false;
            if (line == 1) {
                line1 = true;
            }
            else if (line == 2) {
                line2 = true;
            }
            else if (line == 3) {
                line3 = true;
            }
            else {
                cout << "Invalid line number." << endl;
                break;
            }
            // metro.editStation(name, line1, line2, line3);
            break;
        }
        case 3: {
            string name;
            cout << "Enter the name of the metro station to remove: ";
            cin.ignore();
            getline(cin, name);
            metro->deleteStation(name);
            break;
        }
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}
void Admin::CustomerServiceMenu(stack<string>Questions) {

    int choice;


    cout << "1. Display All Questions\n";
    cout << "2. Reply to the Questions\n";
    cin >> choice;

    switch (choice) {

    case 1:
        while (!Questions.empty()) {
            UserQuestions.push(Questions.top());
            Questions.pop();
        }
        while (!UserQuestions.empty()) {

            cout << UserQuestions.top() << endl;
            UserQuestions.pop();
        }
        break;

    case 2:
        GetQuestion(Questions);
        break;
    }

}
void Admin::GetQuestion(stack<string>Questions) {

    while (!Questions.empty()) {
        UserQuestions.push(Questions.top()); // push it into another stack
        Questions.pop();
    }

    string reply;

    while (!UserQuestions.empty()) {

        string question = UserQuestions.top();
        cout << question << endl;
        cin >> reply;
        SupportRespones.push(make_pair(question, reply)); // push it into queue
        UserQuestions.pop();

    }

    SendReplies();

}
queue<pair<string, string>> Admin::SendReplies() {
    return SupportRespones;
}
void Admin::addTrainToLine() {
    int trainID;
    cout << "Enter train ID: ";
    cin >> trainID;

    // Check if the train with the given ID already exists
    auto it = find_if(trainss.begin(), trainss.end(), [trainID](Train* train) {
        return train->trainID == trainID;
        });



    if (it != trainss.end()) {
        cout << "Train with ID " << trainID << " already exists." << endl;
        return;
    }

    int line;
    cout << "Choose a line for the new train (1, 2, or 3): ";
    cin >> line;

    if (line != 1 && line != 2 && line != 3) {
        cout << "Invalid line number" << endl;
        return;
    }
    vector<Station*> stations = metro->getStationsForLine(line);
    
    if (stations.empty()) {
        cout << "No stations found for line " << line << endl;
        return;
    }

    // Display available stations for the chosen line 
    //عشان اتأكد انها شغاله صح و ممكن نشيلها بعدين
    cout << "Available stations for line " << line << ":" << endl;
    for (Station* station : stations) {
        cout << station->getName() << endl;
    }

    int capacity;
    cout << "Enter capacity of the train: ";
    cin >> capacity;

    // Create a new train object with the provided info
    Train* newTrain = new Train(trainID, capacity, stations,line);
    trainss.push_back(newTrain);
    cout << "Train with ID " << trainID << " added to Line " << line << "." << endl;
}
void Admin::editTrain() {
    int trainID;
    cout << "Enter the ID of the train you want to edit: ";
    cin >> trainID;
    // Find the train object with the matching ID
    Train* trainToEdit = nullptr;
    for (Train* train : trainss) { // Iterate through all trains in the system
        if (train->trainID == trainID) {
            trainToEdit = train;
            break;
        }
    }
    if (trainToEdit != nullptr) {
        int editChoice;
        cout << "What do you want to edit?" << endl;
        cout << "1. Edit Capacity" << endl;
        cout << "2. Back" << endl;
        cout << "Enter your choice: ";
        cin >> editChoice;
        switch (editChoice) {
        case 1: {
            int newCapacity;
            cout << "Enter the new capacity for the train: ";
            cin >> newCapacity;
            if (newCapacity > 0) {
                trainToEdit->capacity = newCapacity;
                cout << "Train capacity updated successfully." << endl;
            }
            else {
                cout << "Invalid capacity. Please enter a positive value." << endl;
            }
            break;
        }

        case 2:
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    else {
        cout << "Train with ID " << trainID << " not found." << endl;
    }
}
void Admin::writeTrians(ofstream* f)
{
   
    for (int i = 0; i < trainss.size(); i++) {
        trainss[i]->write(f);
    }
}
void Admin::readTrains(ifstream* f)
{
    int trainID;
    int capacity;
    int breakdownDelay = 10;
    int line;
    string lines;
    while (getline(*f, lines)) {
        stringstream ss(lines);
        string id, cap, Line;
        getline(ss,id, ',');
        getline(ss, cap, ',');
        getline(ss, Line, ',');
        Train* t = new Train(stoi(id),stoi(cap),stoi(Line));
        trainss.push_back(t);
    }
}
void Admin::handleBreakDowns() {
    int trainID;
    cout << "Enter the ID of the train that has broken down: ";
    cin >> trainID;

    // Find the train object with the matching ID
    Train* brokenTrain = nullptr;
    for (Train* train : trainss) { // Iterate through all trains in the system
        if (train->trainID == trainID) {
            brokenTrain = train;
            break;
        }
    }

    if (brokenTrain != nullptr) {
        brokenTrain->setBreakdown(true);
        cout << "Train " << trainID << " marked as broken down." << endl;
    }
    else {
        cout << "Train with ID " << trainID << " not found." << endl;
    }
}
void Admin::ETA() {
    int line;
    cout << "Enter the line number (1, 2, or 3) to monitor ETA: ";
    cin >> line;
    // Get the stations for the chosen line from the metro
    vector<Station*> stations = metro->getStationsForLine(line);

    // Display the trains associated with the chosen line and calculate the estimated time to complete the line
    cout << "Trains associated with Line " << line << ":" << endl;
    bool hasTrains = false; // Flag to track if there are trains associated with the line
    for (Train* train : trainss) {
        // Check if the train's route matches the chosen line
        if (train->route == stations) {
            cout << "Train ID: " << train->trainID << ", Capacity: " << train->capacity << endl;
            hasTrains = true;
        }
    }
    // If there are trains associated with the line, calculate and display the estimated time to complete the line
    if (hasTrains) {
        int numStations = stations.size();
        int estimatedTime = numStations * 2; // Each station takes 2 minutes

        // Check if any train on the line is broken down
        for (Train* train : trainss) {
            if (train->route == stations && train->isBreakdown) {
                estimatedTime += train->breakdownDelay; // Add 10 minutes extra if there is a breakdown
                break;
            }
        }

        cout << "Estimated time to complete Line " << line << ": " << estimatedTime << " minutes." << endl;
    }
    else {
        cout << "No trains found for Line " << line << "." << endl;
    }
}
void Admin::TrainManagement(Metro* metro1) {
    metro = metro1;
    int choice;
    do {
        cout << "-------------------- Train Management Menu --------------------" << endl;
        cout << "1. Add Train " << endl;
        cout << "2. Edit Train" << endl;
        cout << "3. Handle Break down " << endl;
        cout << "4. Monitor ETA for lines  " << endl;
        cout << "5. Back to Admin Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTrainToLine();
            break;

        case 2: 
            editTrain();
            break;

        case 3: 
            handleBreakDowns();
            break;

        case 4:
            ETA();
            break;

        case 5:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);


}


