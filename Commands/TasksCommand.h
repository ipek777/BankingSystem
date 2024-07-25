#pragma once
#include "BankEmployeeCommand.h"
class TasksCommand :
    public BankEmployeeCommand
{
public:

    TasksCommand(BankEmployee& employee);
    void execute() override;
};

