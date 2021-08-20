/*
 * SourceHandle.cpp
 *
 *  Created on:
 *      Author: Qing
 */

#include "SourceHandle.h"
#include "SqlHandle.h"
#include <sstream>
#include <fstream>
#include <unistd.h>

SourceHandle::SourceHandle() {}

vector<Employee*> SourceHandle::loadCsv(string filename){
	ifstream inputFile(getFilePath(filename));
	vector<Employee*> employees;

	string line;
	Employee* employee;
	vector<string> items;

	getline(inputFile, line);
	while (getline(inputFile, line)) {
		items = split(line, ',');
		employee = new Employee;
		employee->employeeid = stoi(items[0]);
		employee->name = items[1];
		employee->age = stoi(items[2]);
		employee->department = items[3];
		employee->hiredate = items[4];
		employee->salary = stof(items[5]);
		employee->level = stoi(items[6]);
		if (!employee->hiredate.empty()){
			calcTotal(employee);
		}
		employees.push_back(employee);
	}
	return employees;
}

const char* SourceHandle::getFilePath(string filename){
	char* tmp = (char*)malloc(sizeof(char) * 256);
	getcwd(tmp, 256);
	sprintf(tmp,"%s/%s",tmp, filename.c_str());
	return tmp;
}

string SourceHandle::trim(const string& s, char delimiter) {
	const size_t begin = s.find_first_not_of(delimiter);
	if (begin == string::npos) return "";

	const size_t end = s.find_last_not_of(delimiter);
	const size_t range = end - begin + 1;

	return s.substr(begin, range);
}

vector<string> SourceHandle::split(string str, char delimiter){
	stringstream ss(str);
	vector<string> result;

	while(ss.good()) {
	    string substr;
	    getline(ss, substr, delimiter);
	    string word = trim(substr, ' '); //trim extra whitespace
	    if (word != "") result.push_back(word);
	}
	return result;
}

void SourceHandle::calcTotal(Employee* emp){
	emp->subsidy = emp->level*100 + workDuration(emp->hiredate)*100;
	emp->total = emp->salary + emp->subsidy;
}

float SourceHandle::workDuration(string hiredate){
	time_t tHire;
	time_t tNow;
	tm t;
	vector<string> items = split(hiredate, '-');
	t.tm_year = stoi(items[0]) - 1900;
	t.tm_mon = stoi(items[1]) - 1;
	t.tm_mday = stoi(items[2]);
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;
	tHire = mktime(&t);
	time(&tNow);
	return difftime(tNow, tHire)/(60*60*24*365);
}
