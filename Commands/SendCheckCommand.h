#pragma once
#include "Command.h"
#include "ThirdPartyEmployee.h"
#include "Client.h"

class SendCheckCommand :
    public Command
{
public: 

    SendCheckCommand(ThirdPartyEmployee& employee, double sum, const verificationCode code, unsigned EGN, Client& client);
    void execute() override;

private:

    ThirdPartyEmployee& _employee;
    double _sum;
    verificationCode _code;
    unsigned _EGN;
    Client& _client;
};

