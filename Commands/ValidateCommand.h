#pragma once
#include "BankEmployeeCommand.h"
#include "Bank.h"

class ValidateCommand :
    public BankEmployeeCommand
{
public:

    ValidateCommand(BankEmployee& employee, unsigned taskId, Bank& bank);
    void execute() override;

private:

    unsigned _taskId; 
    Bank& _bank;
};

