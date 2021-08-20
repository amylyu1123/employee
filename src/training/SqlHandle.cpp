/*
 * SqlHandle.cpp
 *
 *  Created on: Jun 29, 2021
 *      Author: Qing
 */

#define MY_SORT(emp, category, op) sort(emp.begin(), emp.end(), [&](const Employee* emp_a, const Employee* emp_b){\
	if (op =="desc")\
		return emp_a->category > emp_b->category;\
	return emp_a->category < emp_b->category;\
	})

#include "SqlHandle.h"
#include <algorithm>
#include <regex>

SqlHandle::SqlHandle(vector<Employee*> employees): employees(employees) {}

vector<Employee*> SqlHandle::getEmployees(){
	return employees;
}

void SqlHandle::outputInfo(vector<Employee*> emp, string category){
	vector<string> vec = SourceHandle::split(category, ',');

	for (auto const& v: vec){
		if (v == "employeeid")
			printf("%-15s", v.c_str());
		else if (v == "name")
			printf("%-15s", v.c_str());
		else if (v == "age")
			printf("%-15s", v.c_str());
		else if (v == "department")
			printf("%-20s", v.c_str());
		else if (v == "hiredate")
			printf("%-15s", v.c_str());
		else if (v == "salary")
			printf("%-15s", v.c_str());
		else if (v == "level")
			printf("%-15s", v.c_str());
		else if (v == "subsidy")
			printf("%15s", v.c_str());
		else if (v == "total")
			printf("%15s", v.c_str());
	}
	printf("\n");

	for (auto const& e: emp){
		for (size_t j = 0; j < vec.size(); j++){
			if (vec[j] == "employeeid")
				printf("%-15d", e->employeeid);
			else if (vec[j] == "name")
				printf("%-15s", e->name.c_str());
			else if (vec[j] == "age")
				printf("%-15d", e->age);
			else if (vec[j] == "department")
				printf("%-20s", e->department.c_str());
			else if (vec[j] == "hiredate")
				printf("%-15s", e->hiredate.c_str());
			else if (vec[j] == "salary")
				printf("%-15.2f", e->salary);
			else if (vec[j] == "level")
				printf("%-15d", e->level);
			else if (vec[j] == "subsidy")
				printf("%15.2f", e->subsidy);
			else if (vec[j] == "total")
				printf("%15.2f", e->total);
			if (j == vec.size() - 1)
				printf("\n");
		}
	}
}

void SqlHandle::toUpper(string& value){
	if (allAlpha(value)){
		for (size_t i = 0; i < value.length(); i++){
			if (i == 0) value[i] = toupper(value[i]);
			else if (value[i] == ' ' && i+1 < value.length()) value[i+1] = toupper(value[i+1]);
		}
	}
}

bool SqlHandle::isNat(const string str){
	regex e ("[0-9]+");
	return (regex_match(str, e));
}

bool SqlHandle::checkAge(const string str){
	regex e ("[1-9][0-9]?");
	return (regex_match(str, e));
}

bool SqlHandle::isPosFloat(const string str){
	float value;
	try{
		value = stof(str);
		if (value < 0) return false;
		return true;
	}catch (exception& e){
		return false;
	}
}

bool SqlHandle::allAlpha(const string str){
	vector<string> v = SourceHandle::split(str, ' ');
	for (size_t i = 0; i < v.size(); i++){
		if (!all_of(begin(v[i]), end(v[i]), [](char c){ return isalpha(c);})) return false;
	}
	return true;
}

bool SqlHandle::checkDate(const string str){
	vector<string> date = SourceHandle::split(str, '-');
	if (date.size() != 3) return false;
	if (!SqlHandle::isNat(date[0]) || !SqlHandle::isNat(date[1]) || !SqlHandle::isNat(date[2]))
		return false;

	int year = stoi(date[0]);
	int mon = stoi(date[1]);
	int day = stoi(date[2]);

	time_t now = time(0);
	tm* ptrNow = localtime(&now);
	int currYear = 1900 + ptrNow->tm_year;
	int currMon = 1 + ptrNow->tm_mon;
	int currDay = ptrNow->tm_mday;

	 if (year < 1950 || year > currYear|| mon < 1 || mon > 12 || day < 1 || day > 31)
		 return false;
	 else if (year == currYear && (mon > currMon || (mon == currMon && day > currDay)))
		 return false;
	 else if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
		 return true;
	 else if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && day < 31)
		 return true;

	 if ((year % 4 == 0 && year % 100 !=0) || year % 400 == 0){
		 if (mon == 2 && (day == 28 || day == 30 || day == 31)) return false;
		 	 return true;
	 }else{
		 if (mon == 2 && day > 28) return false;
		 	 return true;
	 }
}

void SqlHandle::updateInfo(Employee* emp, string category, string value){
	if (value.empty() || category.empty())
		throw runtime_error("The SQL command you entered is incorrect!ddd");

	category.erase(remove(category.begin(), category.end(), '\''), category.end());
	value.erase(remove(value.begin(), value.end(), '\''), value.end());
	category.erase(remove(category.begin(), category.end(), '\"'), category.end());
	value.erase(remove(value.begin(), value.end(), '\"'), value.end());

	if (category == "employeeid"){
		if (!isNat(value)) throw runtime_error("The employeeid you entered is not valid!");
		emp->employeeid = stoi(value);
	}
	else if (category == "name"){
		toUpper(value);
		if (!allAlpha(value)) throw runtime_error("The name you entered is not valid!");
		emp->name = value;
	}
	else if (category == "age"){
		if (!checkAge(value)) throw runtime_error("The age you entered is not valid!");
		emp->age = stoi(value);
	}
	else if (category == "department"){
		toUpper(value);
		if (!allAlpha(value)) throw runtime_error("The department you entered is not valid!");
		emp->department = value;
	}
	else if (category == "hiredate"){
		if (!checkDate(value)) throw runtime_error("The hiredate you entered is not valid!");
		emp->hiredate = value;
	}
	else if (category == "salary"){
		if (!isPosFloat(value)) throw runtime_error("The salary you entered is not valid!");
		emp->salary = stof(value);
	}
	else if (category == "level"){
		if (!isNat(value)) throw runtime_error("The level you entered is not valid!");
		emp->level = stoi(value);
	}
	else if (category == "subsidy"){
		if (!isPosFloat(value)) throw runtime_error("The subsidy you entered is not valid!");
			emp->subsidy = stof(value);
	}

	else if (category == "total"){
		if (!isPosFloat(value)) throw runtime_error("The total you entered is not valid!");
		emp->total = stof(value);
	}
	else
		throw runtime_error("The information of the employee you entered is incorrect!dd");
}

vector<Employee*> SqlHandle::findTarget(string category, string value){
	vector<Employee*> emp;

	//remove extra quotes
	category.erase(remove(category.begin(), category.end(), '\''), category.end());
	value.erase(remove(value.begin(), value.end(), '\''), value.end());
	category.erase(remove(category.begin(), category.end(), '\"'), category.end());
	value.erase(remove(value.begin(), value.end(), '\"'), value.end());

	for (size_t i = 0; i < employees.size(); i++){
		if (category == "employeeid"){
			if (!isNat(value)) throw runtime_error("The employeeid you entered is not valid!");
			if (employees[i]->employeeid == (unsigned int)stoi(value))
				emp.push_back(employees[i]);
		}
		else if (category == "name"){
			toUpper(value);
			if (!allAlpha(value)) throw runtime_error("The name you entered is not valid!");
			if (employees[i]->name == value)
				emp.push_back(employees[i]);
		}
		else if (category == "age"){
			if (!checkAge(value)) throw runtime_error("The age you entered is not valid!");
			if (employees[i]->age == (unsigned int)stoi(value))
				emp.push_back(employees[i]);
		}
		else if (category == "department"){
			toUpper(value);
			if (!allAlpha(value)) throw runtime_error("The department you entered is not valid!");
			if (employees[i]->department == value)
				emp.push_back(employees[i]);
		}
		else if (category == "hiredate" && employees[i]->hiredate == value){
			if (!checkDate(value)) throw runtime_error("The hiredate you entered is not valid!");
			emp.push_back(employees[i]);
		}
		else if (category == "salary"){
			if (!isPosFloat(value)) throw runtime_error("The salary you entered is not valid!");
			if (employees[i]->salary == stof(value))
				emp.push_back(employees[i]);
		}
		else if (category == "level"){
			if (!isNat(value)) throw runtime_error("The level you entered is not valid!");
			if (employees[i]->level == (unsigned int)stoi(value))
				emp.push_back(employees[i]);
		}
		else if (category == "subsidy"){
			if (!isPosFloat(value)) throw runtime_error("The subsidy you entered is not valid!");
			if (employees[i]->subsidy == stof(value))
				emp.push_back(employees[i]);
		}
		else if (category == "total"){
			if (!isPosFloat(value)) throw runtime_error("The total you entered is not valid!");
			if (employees[i]->total == stof(value))
				emp.push_back(employees[i]);
		}
		else throw runtime_error("The information of the employee you entered is incorrect!");
	}
	return emp;
}
void SqlHandle::select(string command){
	vector<string>com = SourceHandle::split(command, ' ');
	if (com.size() < 4 || com[0] != "select" || command.find("from") == string::npos ||
			command.find("tbl_salary") == string::npos)
		throw runtime_error("The SQL command you entered is incorrect!");

	string categories;
	size_t index;

	//size >= 4
	for (index = 1; index < com.size(); index++){
		if (com[index] != "from")
			categories += com[index];
		else{
			if (index + 1 < com.size() && com[index+1] != "tbl_salary"){
				throw runtime_error("The table name is incorrect! Please use 'tbl_salary'.");
			}
			index += 2;
			break;
		}
	}

	vector<string>target;
	vector<Employee*>emp;
	string temp;
	string col;

	if (command.find("where") == string::npos && command.find("order") == string::npos){
		if (com.size() != 4) throw runtime_error("The SQL command you entered is incorrect!");
	}

	if (index+1 < com.size() && com[index+1] == "where"){
		for (size_t j = index+2; j < com.size(); j++){
			if (com[j] != "order"){
				temp = temp + com[j] + " ";
			}
			else{
				index = j;
				break;
			}
		}
		if (temp.empty())
			throw runtime_error("The SQL command you entered is incorrect!");
		target = SourceHandle::split(temp, '=');
		emp = findTarget(target[0], target[1]);
	}
	else emp = employees;

	if (command.find("order") != string::npos){
		if (command.find("where") != string::npos && command.find("order") < command.find("where"))
				throw runtime_error("The SQL command you entered is incorrect!");
		if ((index < com.size() && com[index] != "order") || (index+1 < com.size() && com[index+1] != "by"))
			throw runtime_error("The SQL command you entered is incorrect!");
		if (com.back() == "desc" || com.back() == "asc") col = com[com.size() - 2];
		else col = com[com.size() - 1];
		if (col == "employeeid")//select * from tbl_salary order by employeeid
			MY_SORT(emp, employeeid, com[com.size()-1]);
		else if (col == "name")
			MY_SORT(emp, name, com[com.size()-1]);
		else if (col == "age")
			MY_SORT(emp, age, com[com.size()-1]);
		else if (col == "department")
			MY_SORT(emp, department, com[com.size()-1]);
		else if (col == "hiredate")
			MY_SORT(emp, hiredate, com[com.size()-1]);
		else if (col == "salary")
			MY_SORT(emp, salary, com[com.size()-1]);
		else if (col == "level")
			MY_SORT(emp, level, com[com.size()-1]);
		else if (col == "subsidy")
			MY_SORT(emp, subsidy, com[com.size()-1]);
		else if (col == "total")
			MY_SORT(emp, total, com[com.size()-1]);
		else
			throw runtime_error("The column that you want to order by is incorrect!");
	}

	if (categories == "*"){
		categories = "employeeid, name, age, department, hiredate, salary, level, subsidy, total";
	}
	else{
		vector<string>cate = SourceHandle::split(categories, ',');
		for (size_t i = 0; i < cate.size(); i++){
			if (cate[i] == "employeeid" || cate[i] == "name" || cate[i] == "age" || cate[i] == "department" ||
					cate[i] == "hiredate" || cate[i] == "salary" || cate[i] == "level" || cate[i] == "subsidy" ||
					cate[i] == "total")
				continue;
			else throw runtime_error("The column that you want to select is invalid!");
		}
	}
	outputInfo(emp, categories);
}

void SqlHandle::insert(string command){
	vector<string>com = SourceHandle::split(command, ' ');

	if (com.size() < 6 || com[0] != "insert" || com[1] != "into" || command.find("(") == string::npos \
			|| command.find(")") == string::npos){
		throw runtime_error("The SQL command you entered is incorrect!");
	} else if (com[2] != "tbl_salary"){
		throw runtime_error("The table name is incorrect! Please use 'tbl_salary'.");
	}

	//check if tbl_salary (, )values(, ends with )
	for (size_t i = 0; i < com.size(); i++){
		if (i == 3 && com[i][0] != '(')
			throw runtime_error("The SQL command you entered is incorrect!");
		else if (i < com.size()-1 && com[i].back() == ')' && (com[i+1] != "values" || com[i+2][0] != '(')){
			throw runtime_error("The SQL command you entered is incorrect!");
		}else if (i == com.size()-1 && com[i].back() != ')'){
			throw runtime_error("The SQL command you entered is incorrect!");
		}else if (com[i] == "values" && com[i-1].back() != ')')
			throw runtime_error("The SQL command you entered is incorrect!");
	}
	vector<string> category;
	vector<string> values;
	Employee* emp;

	category = SourceHandle::split(command.substr(command.find("(") + 1, (command.find(")") - command.find("(")) - 1), ',');
	command = command.substr(command.find(")") + 1);
	values = SourceHandle::split(command.substr(command.find("(") + 1, (command.find(")") - command.find("(")) - 1), ',');

	if (category.size() != values.size() || category.size() != 7){
		throw runtime_error("Please try to include all and only the following information of the employee "
				"you want to insert: employeeid, name, age, department, hiredate, salary, level.");
	}

	emp = new Employee;
	for (size_t i = 0; i < category.size(); i++){
		//check if we insert duplicate employee by employeeid and name
		if (category[i] == "employeeid" || category[i] == "name"){
			for (size_t j = 0; j < employees.size(); j++){
				values[i].erase(remove(values[i].begin(), values[i].end(), '\''), values[i].end());
				values[i].erase(remove(values[i].begin(), values[i].end(), '\"'), values[i].end());
				toUpper(values[i]);
				if (to_string(employees[j]->employeeid) == values[i] || employees[j]->name == values[i]){
					delete emp;
					throw runtime_error("You inserted a duplicate employee!");
				}
			}
		}
		else if (category[i] == "subsidy" || category[i] == "total") {
			throw runtime_error("Please try to include all of the following of the employee you want to insert:\n"
								" employeeid, name, age, department, hiredate, salary, level.");
		}
		updateInfo(emp, category[i], values[i]);
	}
	SourceHandle::calcTotal(emp);
	employees.push_back(emp);
}

void SqlHandle::update(string command){
	vector<string>com = SourceHandle::split(command, ' ');
	if (com[0] != "update" || com[2] != "set")
		throw runtime_error("The SQL command you entered is incorrect!");
	else if (com[1] != "tbl_salary")
		throw runtime_error("The table name is incorrect! Please use 'tbl_salary'.");
	if (command.find("where") == string::npos)
		throw runtime_error("The SQL command you entered is incorrect!");

	string update;
	string target;
	bool found = false;

	for (size_t i = 3; i < com.size(); i++){
		if (com[i] != "where" && !found){
			update = update + com[i] + " ";
		}
		else if (com[i] == "where") found = true;
		else if (found)
			target += com[i];
	}

	vector<string>info = SourceHandle::split(update, ',');
	vector<string>categories;
	vector<string>values;
	vector<string>tmp;

	for (size_t i = 0; i < info.size(); i++){
		tmp = SourceHandle::split(info[i], '=');
		if (tmp[0] == "" || tmp[1] == "")
			throw runtime_error("The updated information is incomplete!");
		else if (tmp[0] == "employeeid" || tmp[0] == "name" || tmp[0] == "subsidy" || tmp[0] == "total")
			throw runtime_error("The 'employeeid', 'name', 'subsidy', 'total' of an employee cannot be changed! Please do not update any of them.");
		categories.push_back(tmp[0]);
		values.push_back(tmp[1]);
	}

	vector<string>employee = SourceHandle::split(target, '=');
	vector<Employee*> updated = findTarget(employee[0], employee[1]);
	if (updated.size() == 0)
		throw runtime_error("The employee(s) you want to update cannot be found!"); //category incorrect

	for (size_t i = 0; i < employees.size(); i++){
		for (size_t k = 0; k < updated.size(); k++){
			if (updated[k]->employeeid == employees[i]->employeeid){
				for (size_t j = 0; j < categories.size(); j++){
					updateInfo(employees[i], categories[j], values[j]);
					if (categories[j] == "salary" || categories[j] == "level" || categories[j] == "hiredate")
						SourceHandle::calcTotal(employees[i]);
				}
			}
		}
	}
}

void SqlHandle::deleteEmployee(string command){
	vector<string>com = SourceHandle::split(command, ' ');
	string target;

	if (com.size() < 5 || com[0] != "delete" || com[1] != "from" || com[3] != "where")
		throw runtime_error("The SQL command you entered is incorrect!");
	else if (com[2] != "tbl_salary")
		throw runtime_error("The table name is incorrect! Please use 'tbl_salary'.");

	for (size_t i = 4; i < com.size(); i++){
		target += com[i];
	}

	vector<string>employee = SourceHandle::split(target, '=');
	if (employee.size() != 2) throw runtime_error("The information of the employee is incorrect!");
	vector<Employee*> updated = findTarget(employee[0], employee[1]);

	if (updated.size() == 0)
		throw runtime_error("The employee you want to delete has not been found!");

	for (size_t i = 0; i < employees.size(); i++){
		for (size_t j = 0; j < updated.size(); j++){
			if (employees[i]->employeeid == updated[j]->employeeid){
				delete employees[i]; //delete pointer
				employees.erase(employees.begin() + i); //erase from the vector, employees
			}
		}
	}
}
