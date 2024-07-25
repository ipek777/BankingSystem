#pragma once
#include "MessageVisitor.h"
#include "Task.h"

class ApproveMessageVisitor : public MessageVisitor 
{
public:

    ApproveMessageVisitor(Task& task, const MyString& eName);

    void visit(OpenRequest& request) override;
    void visit(CloseRequest& request) override;
    void visit(ChangeRequest& request) override;

private:

    Task& _task;
    MyString _eName;

};


