#include "CloseCommand.h"

CloseCommand::CloseCommand(Client& client, const MyString& bankName, unsigned accountID, Bank& bank) : ClientCommand(client),
																							_bankName(bankName),
																							_accountID(accountID),
																						    _bank(bank)
{
}

void CloseCommand::execute()
{
	Request* request = _client.close(_bankName, _accountID);
	_bank.issueTask(request);
}
