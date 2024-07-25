#pragma once
#include "Request.h"
#include "MyString.h"
#include <iostream>

class Client;
class Request;
class MessageVisitor; 

class ChangeRequest : public Request
{
protected:

	MyString _newBankName;
	MyString _currBankName;
	unsigned _accountID;

public:

	ChangeRequest(const MyString& newBankName, const MyString& currBankName, unsigned accountID, Client& issuer);

	const MyString& getNewBankName() const;
	const MyString& getCurrentBankName() const;
	unsigned getAccountID() const;
	Request* clone() const override;
	void accept(MessageVisitor& visitor) override;

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};


