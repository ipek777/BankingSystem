#pragma once
#include "Command.h"
#include "Client.h"

class ClientCommand : public Command
{
public:
	ClientCommand(Client& client);

protected:
	Client& _client;

};

