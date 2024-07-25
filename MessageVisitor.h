#pragma once
#include "OpenRequest.h"
#include "CloseRequest.h"
#include "ChangeRequest.h"
#include "Client.h"


class OpenRequest;
class CloseRequest;
class ChangeRequest;

class MessageVisitor {
public:
    virtual void visit(OpenRequest& request) = 0;
    virtual void visit(CloseRequest& request) = 0;
    virtual void visit(ChangeRequest& request) = 0;
    virtual ~MessageVisitor() = default;

};
