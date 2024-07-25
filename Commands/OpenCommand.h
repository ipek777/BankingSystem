#pragma once
#include "ClientCommand.h"
#include "Bank.h"

class OpenCommand :
    public ClientCommand
{
public:

    OpenCommand(Client& client, const MyString& bankName, Bank& bank);
    void execute() override;

private:

    MyString _bankName;
    Bank& _bank;
};

