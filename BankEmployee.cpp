#include "BankEmployee.h"

BankEmployee::BankEmployee(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password, const MyString& bankName) : User(firstName, surname, EGN, age, password), 
																																								_bankName(bankName)
{
}

void BankEmployee::addTaskptr(Task* task)
{
	_tasks.push_back(task);
}

void BankEmployee::addTask(const Task& task)
{
	_tasks.push_back(task);
}

void BankEmployee::removeTaskAt(unsigned idx)
{
	_tasks.erase(idx);
}

size_t BankEmployee::getTasksCount() const
{
	return _tasks.size();
}

const Task* BankEmployee::getTask(unsigned idx) const
{
	if (!_tasks.containsAt(idx))
	{
		throw std::invalid_argument("Incorrect index.");
	}

	return &_tasks[idx];
}

void BankEmployee::tasks() const
{
	for (size_t i = 0; i < _tasks.capacity(); i++)
	{
		if(_tasks.containsAt(i))
		{
			std::cout << i << ". ";
			_tasks[i].print();
		}
	}
}

void BankEmployee::view(unsigned idx) const
{
	if (!_tasks.containsAt(idx))
	{
		throw std::invalid_argument("Incorrect index.");
	}

	_tasks[idx].print();
	_tasks[idx].getRequest()->getIssuer().whoami();  
}

void BankEmployee::approve(unsigned idx)
{
	if (!_tasks.containsAt(idx))
	{
		throw std::invalid_argument("Incorrect index.");
	}

	Task& task = _tasks[idx];
	SharedPtr<Request> request = task.getRequest();

	if (!request.isInitlized())
	{
		throw std::runtime_error("Invalid request.");
	}

	if (request->getRequestType() == RequestType::CHANGE && task.getState() == TaskState::DISSAPPROVED)
	{
		throw std::runtime_error("The task needs to be validated first!");
	}

	executeApprove(idx);

	ApproveMessageVisitor visitor(_tasks[idx], _firstName);
	_tasks[idx].processMessage(visitor);
	removeTaskAt(idx);
}

void BankEmployee::disapprove(unsigned idx, const MyString& message)
{
	if (!_tasks.containsAt(idx))
	{
		throw std::invalid_argument("Incorrect index.");
	}
	 
	_tasks[idx].setState(TaskState::DISSAPPROVED);
	DisapproveVisitor visitor(_tasks[idx], message, _firstName);
	_tasks[idx].processMessage(visitor);
	removeTaskAt(idx);
}

Task* BankEmployee::validate(unsigned idx)
{
	if (!_tasks.containsAt(idx))
	{
		throw std::invalid_argument("Incorrect index.");
	}

	_tasks[idx].setState(TaskState::AWAITING_VALIDATION);
	_tasks[idx].refreshDescription();
	return &_tasks[idx];
}

void BankEmployee::help() const
{
	User::help();
	std::cout << "tasks - see all of your current tasks\n";
	std::cout << "view - view a specific task by index\n";
	std::cout << "approve - approve a task by index\n";
	std::cout << "disapprove - disapprove a task by index\n";
	std::cout << "validate - send a task out for validation\n";
}

void BankEmployee::setFromFile(const User& user, const MyString& bankName, const MyVector<Task>& vec)
{
	_firstName = user.getFirstName();
	_surname = user.getSurname();
	_age = user.getAge();
	_EGN = user.getEGN();
	_password = user.getPassword();

	_bankName = bankName;
	if (vec.size() != 0)
	{
		_tasks = ArrayOfPointers<Task>(vec.size());

		for (size_t i = 0; i < vec.size(); i++)
		{
			_tasks.push_back(vec[i]);
		}
	}
	
}

void BankEmployee::saveToFile(std::ofstream& ofs) const
{
	User::saveToFile(ofs);
	_bankName.saveToFile(ofs);

	int tSize = _tasks.size();
	ofs.write((const char*)&tSize, sizeof(tSize));

	for (size_t i = 0; i < _tasks.capacity(); i++)
	{
		if (_tasks.containsAt(i))
		{
			_tasks[i].saveToFile(ofs);
		}
	}
}

void BankEmployee::executeApprove(unsigned idx)
{
	Task& task = _tasks[idx];
	Request* request = task.getRequest().get();

	switch (request->getRequestType())
	{
	case RequestType::OPEN:
	{
		task.setState(TaskState::APPROVED);
		Client& issuer = request->getIssuer();
		Account newAccount(_bankName);
		issuer.addAccount(newAccount);
		break;
	}
	case RequestType::CLOSE:
	{
		CloseRequest* closeRequest = dynamic_cast<CloseRequest*>(request);
		if (!closeRequest)
		{
			throw std::runtime_error("Invalid request type for CLOSE operation.");
		}

		task.setState(TaskState::APPROVED);
		Client& issuer = request->getIssuer();
		issuer.removeAccountByID(closeRequest->getAccountID());
		break;
	}
	case RequestType::CHANGE:
	{
		ChangeRequest* changeRequest = dynamic_cast<ChangeRequest*>(request);
		if (!changeRequest)
		{
			throw std::runtime_error("Invalid request type for CHANGE operation.");
		}

		if (_tasks[idx].getState() == TaskState::VALIDATED)
		{
			task.setState(TaskState::APPROVED);
			Client& issuer = request->getIssuer();
			issuer.removeAccountByID(changeRequest->getAccountID());
			Account newAccount(changeRequest->getNewBankName());
			issuer.addAccount(newAccount);
		}
		else
		{
			_tasks[idx].setState(TaskState::VALIDATED);
			_tasks[idx].refreshDescription();
		}
		break;
	}
	default:
		break;
	}
}
