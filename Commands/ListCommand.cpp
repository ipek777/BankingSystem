#include "ListCommand.h"

ListCommand::ListCommand(Client& client, const MyString& bankName) : ClientCommand(client),
																	_bankName(bankName)
{

}

void ListCommand::execute()
{
	_client.list(_bankName);
}
