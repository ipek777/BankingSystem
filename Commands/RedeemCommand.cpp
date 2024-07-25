#include "RedeemCommand.h"
#pragma warning (disable : 4996)


RedeemCommand::RedeemCommand(Client& client, const MyString& bankName, unsigned accountID, const verificationCode code) : ClientCommand(client),
																															_bankName(bankName),
																															_accountID(accountID)
{
	strcpy(_code, code);
}

void RedeemCommand::execute()
{
	_client.redeem(_bankName, _accountID, _code);
}
