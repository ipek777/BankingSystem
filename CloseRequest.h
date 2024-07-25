#pragma once
#include "Request.h"


class Request;
class MessageVisitor;

class CloseRequest : public Request
{
private:

	MyString _bankName;
	unsigned _accountID;

public:

	CloseRequest(const MyString& bankName, unsigned accountID, Client& issuer);
	Request* clone() const override;
	void accept(MessageVisitor& visitor) override;
	const MyString& getBankName() const;
	unsigned getAccountID() const;


	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

