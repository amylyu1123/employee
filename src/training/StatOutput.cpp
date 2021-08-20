/*
 * Stat.cpp
 *
 *  Created on: Jun 24, 2021
 *      Author: Amy
 */

#include "StatOutput.h"
#include <fstream>
#include <unistd.h>
#include <map>
#include <algorithm>
#include <math.h>

StatOutput::StatOutput(vector<Employee*> employees): employees(employees) {}

void StatOutput::generateHtml(const string& filename, const string& type, const string& title, const string& data, const string& categories, const string& values){
	ofstream myfile;
	char tmp[256];
	getcwd(tmp, 256);
	sprintf(tmp, "%s/%s", tmp, filename.c_str());
	myfile.open(tmp);

	myfile << "<!DOCTYPE html>\n";
	myfile << "<html>\n";
	myfile << "<head>\n";
	myfile << "<meta charset=\"utf-8\">\n";
	myfile << "<title>ECharts</title>\n";
	myfile << "<script src=\"echarts.min.js\"></script>\n";
	myfile << "</head>\n";
	myfile << "<body>\n";
	myfile << "<div id=\"main\" style=\"width: 1800px;height:900px;\"></div>\n";
	myfile << "<script type=\"text/javascript\">\n";
	myfile << "var myChart = echarts.init(document.getElementById('main'));\n";

	if (type == "gauge"){
		myfile << "var option = {tooltip: {formatter: '{a} <br/>{b} : {c}%'}, series: [{name: 'Pressure',type: 'gauge',detail: {"
				"formatter: '{value}'},data: [{value: ";
		myfile << values;
		myfile << ",name: \'";
		myfile << data << "\'}]}]};\n";
	}
	else{
		myfile << "var option = {title: {text: \'";
		myfile << title;
		myfile << "\'},tooltip: {},legend: {data:[\'";
		myfile << data;
		myfile << "\']""},xAxis: {type: 'category',data: [";
		myfile << categories;
		myfile << "]},yAxis: {type: 'value'},series: [{data: [";
		myfile << values;
		myfile << "],type: \'";
		myfile << type << "\'}]}\n";
	}
	myfile << "myChart.setOption(option);\n</script>\n</body>\n</html>";
	myfile.close();
}

void StatOutput::total(){
	float total = 0;
	for (size_t i = 0; i < employees.size(); i++){
		total += employees[i]->total;
	}
	generateHtml("total.html", "gauge", "", "TOTAL SALARY", "", to_string(total));
}

void StatOutput::dept(){
	map<string, float> deptTotal;
	for (size_t i = 0; i < employees.size(); i++){
		if (deptTotal.count(employees[i]->department) != 1)
			deptTotal[employees[i]->department] = 0;
		deptTotal[employees[i]->department] += employees[i]->total;
	}
	string dept;
	string total;
	for (auto const& item: deptTotal){
		dept = dept + "\'" + item.first + "\',";
		total = total + to_string(deptTotal[item.first]) + ",";
	}
	generateHtml("dept.html", "bar", "Total Salary by Department", "Total Salary", dept.substr(0, dept.size() - 1), total.substr(0, total.size() - 1));
}

void StatOutput::date(){
	map<string, int> yearNum;
	string hireyear;
	for (size_t i = 0; i < employees.size(); i++){
		hireyear = employees[i]->hiredate.substr(0, 4);
		if (yearNum.count(hireyear) != 1)
			yearNum[hireyear] = 0;
		yearNum[hireyear]++;
	}
	string year;
	string num;
	for (auto const& item: yearNum){
		year = year + "\'" + item.first + "\',";
		num = num + to_string(yearNum[item.first]) + ",";
	}
	generateHtml("date.html", "bar", "Number of Employees by Hire Year", "Number of Employees", year.substr(0, year.size() - 1), num.substr(0, num.size() - 1));
}

struct Salary {
	float total;
	int count;
};

void StatOutput::level(){
	map<int, Salary> levelAvg;

	for (size_t i = 0; i < employees.size(); i++){
		if (levelAvg.count(employees[i]->level) != 1){
			Salary s = {employees[i]->total, 1};
			levelAvg[employees[i]->level] = s;
		}
		levelAvg[employees[i]->level].total += employees[i]->total;
		levelAvg[employees[i]->level].count += 1;
	}

	string level;
	string avg;
	for (const auto& item: levelAvg){
		level = level + "\'" + to_string(item.first) + "\',";
		avg = avg + to_string(levelAvg[item.first].total / levelAvg[item.first].count) + ","; //calculate the average salary for each level
	}
	generateHtml("level.html", "line", "Average Salary by Level", "Average Salary", level.substr(0, level.size() - 1), avg.substr(0, avg.size() - 1));
}

void StatOutput::age(){
	map<int, float> ageNum;
	int age;
	for (size_t i = 0; i < employees.size(); i++){
		age = employees[i]->age - (employees[i]->age % 10); //Convert each employee's age into 10's
		if (ageNum.count(age) != 1)
			ageNum[age] = 0;
		ageNum[age] += employees[i]->total;
	}

	string ages;
	string num;
	for (auto const& item: ageNum){
		ages = ages + "\'" + to_string(item.first) + "-" + to_string(item.first + 9) + "\',";
		num = num + to_string(ageNum[item.first]) + ",";
	}
	generateHtml("age.html", "bar", "Total Salary by Age", "Total Salary", ages.substr(0, ages.size() - 1), num.substr(0, num.size() - 1));
}

bool StatOutput::compare(const Employee* a, const Employee* b){
	return a->total < b->total;
}

void StatOutput::min(){
	vector<Employee*> copy = employees;
	sort(copy.begin(), copy.end(), compare); //sort employees by ascending total salary

	string id;
	string salary;
	for (int i = 0; i < 10; i++){
		id = id + "\'" + to_string(copy[i]->employeeid) + "\',";
		salary = salary + to_string(copy[i]->total) + ",";
	}
	generateHtml("min.html", "bar", "First 10 employee id with lowest total salary", "Total Salary", id.substr(0, id.size() - 1), salary.substr(0, salary.size() - 1));
}
