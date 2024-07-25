#include "CheckAvlCommand.h"

CheckAvlCommand::CheckAvlCommand(Client& client, const MyString& bankName, unsigned accountID) : ClientCommand(client),
																								_bankName(bankName),
																								_accountID(accountID)
{
}

void CheckAvlCommand::execute()
{
	std::cout << _client.check_avl(_bankName, _accountID) << "$ available.\n";
}
