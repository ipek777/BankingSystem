#include "ApproveCommand.h"

ApproveCommand::ApproveCommand(BankEmployee& employee, unsigned taskId) : BankEmployeeCommand(employee),
																		 _taskId(taskId)
{
}

void ApproveCommand::execute()
{
	_employee.approve(_taskId);
}
