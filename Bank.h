#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "BankEmployee.h"
#include "Request.h"

class Bank
{
public:

	Bank() = default;
	Bank(const MyString& name);
	Bank(MyString&& name);

	void addEmployee(const BankEmployee& employee);
	void issueTask(Request* request);
	void issueTask(const Task& task);

	const MyString& getName() const;
	int getEmployeeIdx(unsigned EGN) const;
	BankEmployee& getEmployee(unsigned idx);
	
	void setFromFile(const MyString& name, const MyVector<BankEmployee>& vec);
	void saveToFile(std::ofstream& ofs) const;

private:

	MyString _name;
	MyVector<BankEmployee> _employees;

	int findEmployeeForTask() const;

};

