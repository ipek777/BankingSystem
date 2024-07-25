#pragma once
#include "BankEmployeeCommand.h"
class ApproveCommand : 
    public BankEmployeeCommand
{
public:

    ApproveCommand(BankEmployee& employee, unsigned taskId);
    void execute() override;

private:
    
    unsigned _taskId;
};

