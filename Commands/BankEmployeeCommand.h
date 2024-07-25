#pragma once
#include "Command.h"
#include "BankEmployee.h"

class BankEmployeeCommand :
    public Command
{
public:

    BankEmployeeCommand(BankEmployee& employee);

protected:

    BankEmployee& _employee;
};

