#pragma once
#include "MyString.h"
class Account
{
public:

	Account() = default;
	Account(const MyString& bankName);
	Account(const Account& other);
	unsigned getAccountID() const;
	const MyString& getBankName() const;
	double getBalance() const;

	void setBalance(double balance); 
	void print() const;


	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

private:

	unsigned _accountID = 0;
	MyString _bankName;
	double _balance = 0;

	static unsigned _accountsIDRecord;
};

bool operator==(const Account& lhs, const Account& rhs);