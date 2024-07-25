#pragma once
#include "Request.h"
#include "MyString.h"
#include "Client.h"
#include "SharedPtr.hpp"

enum class TaskState
{
	APPROVED,
	DISSAPPROVED,
	VALIDATED, 
	AWAITING_VALIDATION	

};

class Task
{
public:

	Task() = default;
	Task(SharedPtr<Request> request);
	void print() const;
	SharedPtr<Request> getRequest() const;
	TaskState getState() const;
	void setState(TaskState state);
	void refreshDescription();
	void processMessage(MessageVisitor& visitor);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs, RequestType type, Client& issuer);

private:

	SharedPtr<Request>  _request;
	MyString _description;
	TaskState _state = TaskState::DISSAPPROVED;

	void createDescription();

};

