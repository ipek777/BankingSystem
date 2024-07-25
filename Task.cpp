#include "Task.h"

void Task::createDescription()
{
	switch (_request->getRequestType())
	{

	case RequestType::OPEN:
	{
		_description = "OPEN request";
		return;
	}

	case RequestType::CLOSE:
	{
		_description = "CLOSE request";
		return;
	}

	case RequestType::CHANGE:
	{
		_description = "CHANGE request";
		if (_state == TaskState::AWAITING_VALIDATION)
		{
			_description += " (Awaiting validation of personal information)";
		}
		else if (_state == TaskState::VALIDATED)
		{
			_description += " (Validated)";
		}
		return;
	}

	default:

		_description = "Unknown task.";
		return;
	}
}

Task::Task(SharedPtr<Request> request) : _request(request)
{
	createDescription();
}

void Task::print() const
{
	
	std::cout << _description <<'\n';
}

SharedPtr<Request> Task::getRequest() const
{
	return _request;
}

TaskState Task::getState() const
{
	return _state;
}

void Task::setState(TaskState state)
{
	_state = state;
}

void Task::refreshDescription()
{
	createDescription();
}

void Task::processMessage(MessageVisitor& visitor) 
{
	_request->accept(visitor);
}

void Task::saveToFile(std::ofstream& ofs) const
{
	_request->saveToFile(ofs);
	_description.saveToFile(ofs);
	ofs.write((const char*)&_state, sizeof(_state));
}

void Task::readFromFile(std::ifstream& ifs, RequestType type, Client& issuer)
{
	switch (type)
	{
	case RequestType::OPEN:
	{
		MyString bankName;
		bankName.readFromFile(ifs);
		Request* ptr = new OpenRequest(bankName, issuer);
		_request = SharedPtr<Request>(ptr);
		break;
	}
	case RequestType::CLOSE:
	{
		MyString bankName;
		unsigned accountID;
		bankName.readFromFile(ifs);
		ifs.read((char*)&accountID, sizeof(accountID));
		Request* ptr = new CloseRequest(bankName, accountID, issuer);
		_request = SharedPtr<Request>(ptr);
		break;
	}
	case RequestType::CHANGE:
	{
		MyString newBankName, currBankName;
		unsigned accountID;
		newBankName.readFromFile(ifs);
		currBankName.readFromFile(ifs);
		ifs.read((char*)&accountID, sizeof(accountID));
		Request* ptr = new ChangeRequest(newBankName, currBankName, accountID, issuer);
		_request = SharedPtr<Request>(ptr);
		break;
	}
	default:
		break;
	}
	_description.readFromFile(ifs);
	ifs.read((char*)&_state, sizeof(_state));
}


