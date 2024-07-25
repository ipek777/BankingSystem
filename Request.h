#pragma once

#include "MyString.h"
#include <iostream>

enum class RequestType
{
	OPEN,
	CLOSE,
	CHANGE
};

class Client;
class MessageVisitor;


class Request
{
protected:

	Client& _issuer;
	RequestType _type;

public:

	Request(Client& issuer, RequestType type);
	Client& getIssuer() const;
	RequestType getRequestType() const;
	virtual  Request* clone() const = 0;
	virtual void accept(MessageVisitor& visitor) = 0;
	virtual ~Request() = default;

	virtual void saveToFile(std::ofstream& ofs) const;
	virtual void readFromFile(std::ifstream& ifs);

};