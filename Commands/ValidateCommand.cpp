#include "ValidateCommand.h"

ValidateCommand::ValidateCommand(BankEmployee& employee, unsigned taskId, Bank& bank) : BankEmployeeCommand(employee),
																						_taskId(taskId),
																						_bank(bank)
{
}

void ValidateCommand::execute()
{
	Task* task = _employee.validate(_taskId);
	_bank.issueTask(*task);
}
