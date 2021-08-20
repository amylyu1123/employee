/*
 * SourceHandle.h
 *
 *  Created on: 2021
 *      Author: Qing
 */

#pragma once
#ifndef SOURCEHANDLE_H_
#define SOURCEHANDLE_H_

#include <iostream>
#include <vector>

using namespace std;

struct Employee {
	unsigned int employeeid;
	string name;
	unsigned int age;
	string department;
	string hiredate;
	float salary;
	unsigned int level;
	float subsidy;
	float total;
};

class SourceHandle {
public:
	SourceHandle();
	vector<Employee*> loadCsv(string filename);
	static const char* getFilePath(string filename);
	static vector<string> split(string str, char delimiter);
	static string trim(const string &s, char delimiter);
	static void calcTotal(Employee* emp);
	static float workDuration(string hiredate);

};

#endif /* SOURCEHANDLE_H_ */
