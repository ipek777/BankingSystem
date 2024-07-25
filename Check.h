#pragma once
#include <iostream>
#include <fstream>

namespace
{
	const size_t codeSize = 4;
	typedef char verificationCode[codeSize];
}

class Check
{
private:

	double _sum = 0;
	verificationCode _code{ 0 };
	bool _isResedeemed = false;
	unsigned _ownerEgn = 0;

public:
	Check() = default;
	Check(double sum, const verificationCode code, unsigned ownerEgn);
	double getSum() const;
	const char* getVerificationCode() const;
	bool IsRedeemed() const;
	unsigned getOwnerEgn() const;

	void setIsRedeemed(bool isRedeemed);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

