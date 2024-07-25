#include "ChangeCommand.h"

ChangeCommand::ChangeCommand(Client& client, const MyString& newBankName, const MyString& currBankName, unsigned accountID, Bank& bank) : ClientCommand(client),
																																_newBankName(newBankName),
																																_currBankName(currBankName),
																																_accountID(accountID),
																																_bank(bank)
{
}

void ChangeCommand::execute()
{
	Request* request = _client.change(_newBankName, _currBankName, _accountID);
	_bank.issueTask(request);
}
