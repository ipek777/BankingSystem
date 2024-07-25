#include "OpenCommand.h"

OpenCommand::OpenCommand(Client& client, const MyString& bankName, Bank& bank) : ClientCommand(client), 
																				_bankName(bankName),
																				_bank(bank)
{
}

void OpenCommand::execute()
{
	Request* request = _client.open(_bankName);
	_bank.issueTask(_client.open(_bankName));
}
