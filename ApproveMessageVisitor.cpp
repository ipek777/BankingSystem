#include "ApproveMessageVisitor.h"

ApproveMessageVisitor::ApproveMessageVisitor(Task& task, const MyString& eName) : _task(task), _eName(eName) {}

void ApproveMessageVisitor::visit(OpenRequest& request) 
{
    MyString message = "Approved opening account at " + request.getBankName() + " by " + _eName;
    _task.getRequest()->getIssuer().addMessage(message);
}

void ApproveMessageVisitor::visit(CloseRequest& request) 
{
    MyString message = "Approve closing account at " + request.getBankName() + " by " + _eName;
    _task.getRequest()->getIssuer().addMessage(message);
}

void ApproveMessageVisitor::visit(ChangeRequest& request) 
{
    MyString message = "Approved changing account from " + request.getCurrentBankName() + " to " + request.getNewBankName() + " by " + _eName;
    _task.getRequest()->getIssuer().addMessage(message);
}