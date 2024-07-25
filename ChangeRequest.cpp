#include "ChangeRequest.h"
#include "MessageVisitor.h"

const MyString& ChangeRequest::getNewBankName() const
{
	return _newBankName;
}

const MyString& ChangeRequest::getCurrentBankName() const
{
	return _currBankName;
}

unsigned ChangeRequest::getAccountID() const
{
	return _accountID;
}

Request* ChangeRequest::clone() const
{
	Request* cloned = new ChangeRequest(*this);
	return cloned;
}

void ChangeRequest::accept(MessageVisitor& visitor)
{
	visitor.visit(*this);
}

void ChangeRequest::saveToFile(std::ofstream& ofs) const
{
	Request::saveToFile(ofs);
	_newBankName.saveToFile(ofs);
	_currBankName.saveToFile(ofs);
	ofs.write((const char*)&_accountID, sizeof(_accountID));
}

void ChangeRequest::readFromFile(std::ifstream& ifs)
{
	Request::readFromFile(ifs);
	_newBankName.readFromFile(ifs);
	_currBankName.readFromFile(ifs);
	ifs.read((char*)&_accountID, sizeof(_accountID));
}

ChangeRequest::ChangeRequest(const MyString& newBankName, const MyString& currBankName, unsigned accountID, Client& issuer) : Request(issuer, RequestType::CHANGE),
																															_newBankName(newBankName),
																															_currBankName(currBankName),
																															_accountID(accountID)
{
}