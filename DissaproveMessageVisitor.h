#pragma once
#include "MessageVisitor.h"
#include "Task.h"
#include "MyString.h"
#include <iostream>

class DisapproveVisitor : public MessageVisitor 
{
public:

    DisapproveVisitor(Task& task, const MyString& reason, const MyString& eName);

    void visit(OpenRequest& request) override;
    void visit(CloseRequest& request) override;
    void visit(ChangeRequest& request) override;

private:

    Task& _task;
    MyString _reason;
    MyString _eName;

};


