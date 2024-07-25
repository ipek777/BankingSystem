#include "Bank.h"

Bank::Bank(const MyString& name) : _name(name)
{
}

Bank::Bank(MyString&& name) : _name(name)
{
}

void Bank::addEmployee(const BankEmployee& employee) 
{
	_employees.push_back(employee);
}

void Bank::issueTask(Request* request)
{
	size_t idx = findEmployeeForTask();
	Task* task = new Task(request);
	_employees[idx].addTaskptr(task); 
}

void Bank::issueTask(const Task& task)
{
	size_t idx = findEmployeeForTask();
	_employees[idx].addTask(task);  
}

const MyString& Bank::getName() const
{
	return _name;
}

int Bank::getEmployeeIdx(unsigned EGN) const
{
	int idx = -1;
	for (size_t i = 0; i < _employees.size(); i++)
	{
		if (_employees[i].getEGN() == EGN)
		{
			idx = i;
			break;
		}
	}
	return idx;
}

BankEmployee& Bank::getEmployee(unsigned idx) 
{
	return _employees[idx];
}

void Bank::setFromFile(const MyString& name, const MyVector<BankEmployee>& vec)
{
	_name = name;
	_employees = vec;
}

void Bank::saveToFile(std::ofstream& ofs) const
{
	_name.saveToFile(ofs);
	int eSize = _employees.size();
	ofs.write((const char*)&eSize, sizeof(eSize));

	for (size_t i = 0; i < eSize; i++)
	{
		_employees[i].saveToFile(ofs);
	}
}

int Bank::findEmployeeForTask() const
{
	int minIdx = 0;
	for (size_t i = 1; i < _employees.size(); i++)
	{
		if (_employees[i].getTasksCount() < _employees[minIdx].getTasksCount())
		{
			minIdx = i;
		}
	}
	return minIdx;
}
