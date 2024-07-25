#include "MessagesCommand.h"

MessagesCommand::MessagesCommand(Client& client) : ClientCommand(client)
{
}

void MessagesCommand::execute()
{
	_client.messages();
}
