#include "TasksCommand.h"

TasksCommand::TasksCommand(BankEmployee& employee) : BankEmployeeCommand(employee)
{
}

void TasksCommand::execute()
{
	_employee.tasks();
}
