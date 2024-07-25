#pragma once
#include "ClientCommand.h"
class MessagesCommand :
    public ClientCommand
{
public:

    MessagesCommand(Client& client);
    void execute() override;
};

