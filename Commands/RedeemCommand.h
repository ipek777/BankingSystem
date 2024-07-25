#pragma once
#include "ClientCommand.h"

class RedeemCommand :
    public ClientCommand
{
public:

    RedeemCommand(Client& client, const MyString& bankName, unsigned accountID, const verificationCode code);
    void execute() override;

private:

    MyString _bankName;
    unsigned _accountID;
    verificationCode _code;
};

