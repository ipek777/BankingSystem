#pragma once
#include "BankEmployeeCommand.h"
class ViewCommand :
    public BankEmployeeCommand
{
public:

    ViewCommand(BankEmployee& employee, unsigned taskId);
    void execute() override;

private:

    unsigned _taskId;
};

