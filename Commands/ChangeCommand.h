#pragma once
#include "ClientCommand.h"
#include "Bank.h"

class ChangeCommand :
    public ClientCommand
{
public:

    ChangeCommand(Client& client, const MyString& newBankName, const MyString& currBankName, unsigned accountID, Bank& bank);
    void execute() override;

private:

    MyString _newBankName;
    MyString _currBankName;
    unsigned _accountID;
    Bank& _bank;
};

