#pragma once
#include "ClientCommand.h"
class ListCommand :
    public ClientCommand
{
public:

    ListCommand(Client& client, const MyString& bankName);
    void execute() override;

private:

    MyString _bankName;
};

