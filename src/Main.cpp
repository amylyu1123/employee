//============================================================================
// Name        : Main.cpp
// Author      : Qing
// Copyright   : Your copyright notice
// Description : Main, get user input and doing the request
//============================================================================

#include <iostream>
#include <algorithm>
#include "training/SourceHandle.h"
#include "training/StatOutput.h"
#include "training/SqlHandle.h"
#include "training/ExportHandle.h"
using namespace std;

int main() {
    string choice;
    string command;
    bool notQuit = true;
    SourceHandle sh = {};
    vector<Employee*> employees = sh.loadCsv("datasheet.csv");

    while (notQuit){
    	cout << "Enter 'sql', 'stat', 'export', 'return' or 'quit': \n";
    	cin >> choice;
    	cin.ignore();
    	transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
    	if (choice == "sql"){
			cout << "You entered 'sql'. \n";
			SqlHandle sql = {employees};
			while (true){
				cout << "The table_name is tbl_salary. Please enter a command for sql or 'return' to return, 'quit' to quit: \n";
				getline (cin, command);
				transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (command == "return") break;
				if (command == "quit") {
					notQuit = false;
					break;
				}
				try{
					if (command.substr(0, 6) == "insert"){
						sql.insert(command);
						cout << "Insert successfully!:)\n";
					}
					else if (command.substr(0, 6) == "update"){
						sql.update(command);
							cout << "Update successfully!:)\n";
					}
					else if (command.substr(0, 6) == "delete"){
						sql.deleteEmployee(command);
							cout << "Delete successfully!:)\n";
					}
					else if (command.substr(0, 6) == "select") sql.select(command);
					else cout << "The SQL command you entered is incorrect! Please try again.\n";
				}
				catch (const exception& e){
					cerr << e.what() << "\n";
				}
			}
			employees = sql.getEmployees();//updated the employees
    	}
    	else if (choice == "stat"){
			cout << "You entered 'stat. \n";
			StatOutput stat = {employees};
			while (true){
				cout << "Please select one 'total', 'dept', 'date', 'level', 'age', 'min' or 'return' to return, 'quit' to quit: \n";
				cin >> command;
				cin.ignore();
				transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (command == "return") break;
				if (command == "quit") {
					notQuit = false;
					break;
				}
				if (command == "total") stat.total();
				else if (command == "dept") stat.dept();
				else if (command == "date") stat.date();
				else if (command == "level") stat.level();
				else if (command == "age") stat.age();
				else if (command == "min") stat.min();
				else cout << "You did not enter a correct command! Please try again.\n";
			}
    	}
    	else if (choice == "export"){
    		cout << "You entered 'export'.\n";
    		ExportHandle exp = {employees};
			while (true){
				cout << "Please choose the type of file to export('xml'/'json') or 'return' to return, 'quit' to quit: \n";
				cin >> command;
				cin.ignore();
				transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (command == "return") break;
				if (command == "quit") {
					notQuit = false;
					break;
				}
				if (command == "xml") exp.writeXml("datasheet.xml");
				else if (command == "json") exp.writeJson("datasheet.json");
				else cout << "The type of file you entered is incorrect! Please try again.\n";
			}
    	}
    	else if (choice == "return") cout << "You are at the main page now.\n";
    	else if (choice == "quit"){
    		cout << "Bye! Have a great day!";
    		notQuit = false;
    	}
    	else cout << "You did not enter a correct command! Please try again.\n";
    	if (!notQuit) cout << "Bye! Have a great day!";
	}
    for (size_t i = 0; i < employees.size(); i++){
    	delete employees[i];
    }
    return 0;
}
