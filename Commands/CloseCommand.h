#pragma once
#include "ClientCommand.h"
#include "Bank.h"

class CloseCommand :
    public ClientCommand
{
public:

    CloseCommand(Client& client, const MyString& bankName, unsigned accountID, Bank& bank);
    void execute() override;

private:

    MyString _bankName;
    unsigned _accountID;
    Bank& _bank;
};

