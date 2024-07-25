#include "ViewCommand.h"

ViewCommand::ViewCommand(BankEmployee& employee, unsigned taskId) : BankEmployeeCommand(employee), 
																	_taskId(taskId)
{
}

void ViewCommand::execute()
{
	_employee.view(_taskId);
}
