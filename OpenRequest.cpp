#include "OpenRequest.h"
#include "MessageVisitor.h"


OpenRequest::OpenRequest(const MyString& bankName, Client& issuer) : Request(issuer, RequestType::OPEN),
																	_bankName(bankName)
{
}

Request* OpenRequest::clone() const
{
	Request* cloned = new OpenRequest(*this);
	return cloned;
}

void OpenRequest::accept(MessageVisitor& visitor)
{
	visitor.visit(*this);
}

const MyString& OpenRequest::getBankName() const
{
	return _bankName;
}

void OpenRequest::saveToFile(std::ofstream& ofs) const
{
	Request::saveToFile(ofs);
	_bankName.saveToFile(ofs);
}

void OpenRequest::readFromFile(std::ifstream& ifs)
{
	Request::readFromFile(ifs);
	_bankName.readFromFile(ifs);
}
