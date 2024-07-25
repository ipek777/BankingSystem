#include "Request.h"
#include "Client.h"

Request::Request(Client& issuer, RequestType type) : _issuer(issuer),
													_type(type)
{
}

Client& Request::getIssuer() const
{
	return _issuer;
}

RequestType Request::getRequestType() const
{
	return _type;
}

void Request::saveToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&_type, sizeof(_type));
	_issuer.saveToFile(ofs);
}

void Request::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&_type, sizeof(_type));
	_issuer.readFromFile(ifs);
}
