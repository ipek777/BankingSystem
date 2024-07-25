#include "DisapproveCommand.h"

DisapproveCommand::DisapproveCommand(BankEmployee& employee, unsigned taskId, const MyString& message) : BankEmployeeCommand(employee),
																										_taskId(taskId),
																										_message(message)
{
}

void DisapproveCommand::execute()
{
	_employee.disapprove(_taskId, _message);
}
