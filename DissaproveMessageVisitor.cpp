#include "DissaproveMessageVisitor.h"

DisapproveVisitor::DisapproveVisitor(Task& task, const MyString& reason, const MyString& eName) : _task(task),
                                                                                                _reason(reason), 
                                                                                                _eName(eName)
{
}

void DisapproveVisitor::visit(OpenRequest& request) 
{
    MyString message = "Disapproved opening account at " + request.getBankName() + " by " + _eName + ".Reason: " + _reason;
    _task.getRequest()->getIssuer().addMessage(message);
}

void DisapproveVisitor::visit(CloseRequest& request) 
{
    MyString message = "Disapproved opening account at " + request.getBankName() + " by " + _eName + ".Reason: " + _reason;
    _task.getRequest()->getIssuer().addMessage(message);
}

void DisapproveVisitor::visit(ChangeRequest& request) 
{
    MyString message = "Disapproved changing account from " + request.getCurrentBankName() + " to " + request.getNewBankName() + " by " + _eName + ". Reason: " + _reason;
    _task.getRequest()->getIssuer().addMessage(message);
}