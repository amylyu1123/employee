/*
 * SqlHandle.h
 *
 *  Created on: Jun 29, 2021
 *      Author: Qing
 */

#pragma once
#include "SourceHandle.h"
#ifndef SQLHANDLE_H_
#define SQLHANDLE_H_

class SqlHandle {
private:
	void outputInfo(vector<Employee*> v, string category);
	bool checkDate(const string str);
	void toUpper(string& value);
	bool checkAge(const string str);
	bool isPosFloat(const string str);
	bool allAlpha(const string str);
	void updateInfo(Employee* emp, string category, string value);
	vector<Employee*> findTarget(string category, string value);
	vector<Employee*> employees;

public:
	SqlHandle(vector<Employee*> employees);
	vector<Employee*> getEmployees();
	void select(string command);
	void insert(string command);
	void update(string command);
	void deleteEmployee(string command);
	static bool isNat(const string str);
};

#endif /* SQLHANDLE_H_ */
