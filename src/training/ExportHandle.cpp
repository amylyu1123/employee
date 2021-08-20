/*
 * ExportHandle.cpp
 *
 *  Created on:
 *      Author: Qing
 */

#include "ExportHandle.h"
#include <fstream>
#include <unistd.h>

ExportHandle::ExportHandle(vector<Employee*> emp): employees(emp){}

void ExportHandle::writeXml(string filename){
	ofstream outFile;
	outFile.open(SourceHandle::getFilePath(filename), ios::out);
	outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
	outFile << "<employees xmlns=\"employeeSalaries\">\n";
	for (size_t i = 0; i < employees.size(); i++){
		outFile << "    <employee id=" << "\"" << employees[i]->employeeid << "\">\n";
		outFile << "        <name>" << employees[i]->name << "</name>\n";
		outFile << "        <age>" << employees[i]->age << "</age>\n";
		outFile << "        <department>" << employees[i]->department << "</department>\n";
		outFile << "        <hiredate>" << employees[i]->hiredate << "</hiredate>\n";
		outFile << "        <salary>" << employees[i]->salary << "</salary>\n";
		outFile << "        <level>" << employees[i]->level << "</level>\n";
		outFile << "        <subsidy>" << employees[i]->subsidy << "</subsidy>\n";
		outFile << "        <total>" << employees[i]->total << "</total>\n";
		outFile << "    </employee>\n";
	}
	outFile << "</employees>\n";
	outFile.close();
}

void ExportHandle::writeJson(string filename){
	ofstream outFile;
	outFile.open(SourceHandle::getFilePath(filename), ios::out);
	outFile << "[";
	for (size_t i = 0; i < employees.size(); i++){
		outFile << "{";
		outFile << "\"employeeid\" : \"" << employees[i]->employeeid << "\", ";
		outFile << "\"name\" : \"" << employees[i]->name << "\", ";
		outFile << "\"age\" : \"" << employees[i]->age << "\", ";
		outFile << "\"department\" : \"" << employees[i]->department << "\", ";
		outFile << "\"hiredate\" : \"" << employees[i]->hiredate << "\", ";
		outFile << "\"salary\" : \"" << employees[i]->salary << "\", ";
		outFile << "\"level\" : \"" << employees[i]->level << "\", ";
		outFile << "\"subsidy\" : \"" << employees[i]->subsidy << "\", ";
		outFile << "\"total\" : \"" << employees[i]->total << "\"";
		outFile << "}";
		if (i != employees.size() - 1) outFile << ",\n";
	}
	outFile << "]";
	outFile.close();
}
