#include "SendCheckCommand.h"
#pragma warning (disable : 4996)


SendCheckCommand::SendCheckCommand(ThirdPartyEmployee& employee, double sum, const verificationCode code, unsigned EGN, Client& client) : _employee(employee),
																																		_sum(sum),
																																		_EGN(EGN),
																																		_client(client)
{
	strcpy(_code, code);
}

void SendCheckCommand::execute()
{
	Check* check = _employee.send_check(_sum, _code, _EGN);
	_client.addCheck(*check);
	_client.addMessage("You have been issued a check by " + _employee.getFirstName() + " " + _employee.getSurname() + ". Verification code: " + check->getVerificationCode());
	delete check;
}
