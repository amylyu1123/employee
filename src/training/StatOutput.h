/*
 * Stat.h
 *
 *  Created on: Jun 24, 2021
 *      Author: Qing
 */

#pragma once
#include "SourceHandle.h"
#ifndef STATOUTPUT_H_
#define STATOUTPUT_H_

class StatOutput {
private:
	vector<Employee*> employees;
	void generateHtml(const string& filename, const string& type, const string& title, const string& data, const string& categories, const string& values);
public:
	StatOutput(vector<Employee*> employees);
	void total();
	void dept();
	void date();
	void level();
	void age();
	static bool compare(const Employee* a, const Employee* b);
	void min();
};

#endif /* STATOUTPUT_H_ */
