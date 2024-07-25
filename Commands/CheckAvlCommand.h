#pragma once
#include "ClientCommand.h"
class CheckAvlCommand :
    public ClientCommand
{
public:

    CheckAvlCommand(Client& client, const MyString& bankName, unsigned accountID);
    void execute() override;

private:

    MyString _bankName;
    unsigned _accountID;
};

