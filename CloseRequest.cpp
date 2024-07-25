#include "CloseRequest.h"
#include "MessageVisitor.h"


CloseRequest::CloseRequest(const MyString& bankName, unsigned accountID, Client& issuer) : Request(issuer, RequestType::CLOSE),
																							_bankName(bankName),
																							_accountID(accountID)
{
}

Request* CloseRequest::clone() const
{
	Request* cloned = new CloseRequest(*this);
	return cloned;
}

void CloseRequest::accept(MessageVisitor& visitor)
{
	visitor.visit(*this);
}

const MyString& CloseRequest::getBankName() const
{
	return _bankName;
}

unsigned CloseRequest::getAccountID() const
{
	return _accountID;
}

void CloseRequest::saveToFile(std::ofstream& ofs) const
{
	Request::saveToFile(ofs);
	_bankName.saveToFile(ofs);
	ofs.write((const char*)&_accountID, sizeof(_accountID));
}

void CloseRequest::readFromFile(std::ifstream& ifs)
{
	Request::readFromFile(ifs);
	_bankName.readFromFile(ifs);
	ifs.read((char*)&_accountID, sizeof(_accountID));
}

