#pragma once
#include "Request.h"
#include "MyString.h"


class Request;
class Client;
class MessageVisitor;


class OpenRequest : public Request
{
private:

	MyString _bankName;

public:

	OpenRequest(const MyString& bankName, Client& issuer);
	Request* clone() const override;
	void accept(MessageVisitor& visitor) override;
	const MyString& getBankName() const;

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};



