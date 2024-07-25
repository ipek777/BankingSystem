#pragma once
#include "BankEmployeeCommand.h"
class DisapproveCommand :
    public BankEmployeeCommand
{
public:

    DisapproveCommand(BankEmployee& employee, unsigned taskId, const MyString& message);
    void execute() override;

private:

    unsigned _taskId;
    MyString _message;
};

