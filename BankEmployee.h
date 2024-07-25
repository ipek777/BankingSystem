#pragma once
#include "Task.h"
#include "ArrayOfPointers.hpp"
#include "ApproveMessageVisitor.h"
#include "DissaproveMessageVisitor.h"
#include "User.h"
#include "Account.h"

class BankEmployee :
    public User
{
public:

    BankEmployee() = default;
    BankEmployee(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password, const MyString& bankName);

    void addTaskptr(Task* task);
    void addTask(const Task& task);
    void removeTaskAt(unsigned idx);
    size_t getTasksCount() const;
    const Task* getTask(unsigned idx) const;

    void tasks() const;
    void view(unsigned idx) const;
    void approve(unsigned idx);
    void disapprove(unsigned idx, const MyString& message);
    Task* validate(unsigned idx);

    void help() const override;

    void setFromFile(const User& user, const MyString& bankName, const MyVector<Task>& vec);
    void saveToFile(std::ofstream& ofs) const;

private:

    MyString _bankName;
    ArrayOfPointers<Task> _tasks;

    void executeApprove(unsigned idx);
};

