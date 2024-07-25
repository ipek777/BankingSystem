#pragma once
#include "User.h"
#include "Check.h"

class ThirdPartyEmployee :
    public User
{

public:
    ThirdPartyEmployee() = default;
    ThirdPartyEmployee(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password);
    Check* send_check(double sum, const verificationCode code, unsigned EGN) const;
    void help() const override;
};

