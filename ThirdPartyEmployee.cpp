#include "ThirdPartyEmployee.h"

ThirdPartyEmployee::ThirdPartyEmployee(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password) : User(firstName, surname, EGN, age, password)
{
}

Check* ThirdPartyEmployee::send_check(double sum, const verificationCode code, unsigned EGN) const
{
	Check* check = new Check(sum, code, EGN);
	return check;
}

void ThirdPartyEmployee::help() const
{
	User::help();
	std::cout << "send_check - send a check\n";
}
