#include "Check.h"
#pragma warning (disable : 4996)


Check::Check(double sum, const verificationCode code, unsigned ownerEgn) : _sum(sum),
																			_ownerEgn(ownerEgn)
{
	strcpy(_code, code);
}

double Check::getSum() const
{
	return _sum;
}

const char* Check::getVerificationCode() const
{
	return _code;
}

bool Check::IsRedeemed() const
{
	return _isResedeemed;
}

unsigned Check::getOwnerEgn() const
{
	return _ownerEgn;
}

void Check::setIsRedeemed(bool isRedeemed) 
{
	_isResedeemed = isRedeemed;
}

void Check::saveToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&_sum, sizeof(_sum));
	ofs.write((const char*)&_isResedeemed, sizeof(_isResedeemed));
	ofs.write((const char*)&_ownerEgn, sizeof(_ownerEgn));
	ofs.write((const char*)_code, sizeof(_code));
}

void Check::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&_sum, sizeof(_sum));
	ifs.read((char*)&_isResedeemed, sizeof(_isResedeemed));
	ifs.read((char*)&_ownerEgn, sizeof(_ownerEgn));
	ifs.read((char*)_code, sizeof(_code));
}
