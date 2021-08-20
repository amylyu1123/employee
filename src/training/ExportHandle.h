/*
 * ExportHandle.h
 *
 *  Created on:
 *      Author: Qing
 */

#pragma once
#include "SourceHandle.h"
#ifndef EXPORTHANDLE_H_
#define EXPORTHANDLE_H_

class ExportHandle {
private:
	vector<Employee*> employees;
public:
	ExportHandle(vector<Employee*> emp);
	void writeXml(string filename);
	void writeJson(string filename);

};

#endif /* EXPORTHANDLE_H_ */
