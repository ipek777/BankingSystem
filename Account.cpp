#include "Account.h"

unsigned Account::_accountsIDRecord = 100;

Account::Account(const MyString& bankName) : _bankName(bankName) 
{
    _accountID = _accountsIDRecord;
    _accountsIDRecord++;
}

Account::Account(const Account& other)
{
    _bankName = other._bankName;
    _balance = other._balance;
    _accountID = _accountsIDRecord;
    _accountsIDRecord++;
}

unsigned Account::getAccountID() const
{
    return _accountID;
}

const MyString& Account::getBankName() const
{
    return _bankName;
}

double Account::getBalance() const
{
    return _balance;
}

void Account::setBalance(double balance) 
{
    if (_balance < 0)
    {
        throw std::invalid_argument("The balance must be atleast 0!");
    }
    _balance = balance;
}

void Account::print() const
{
    std::cout << _bankName << " " << _accountID << " " << _balance << '\n';
}

void Account::saveToFile(std::ofstream& ofs) const
{
    _bankName.saveToFile(ofs);
    ofs.write((const char*)&_accountID, sizeof(_accountID));
    ofs.write((const char*)&_balance, sizeof(_balance));
    ofs.write((const char*)&_accountsIDRecord, sizeof(_accountsIDRecord));
}

void Account::readFromFile(std::ifstream& ifs)
{
    _bankName.readFromFile(ifs);
    ifs.read((char*)&_accountID, sizeof(_accountID));
    ifs.read((char*)&_balance, sizeof(_balance));
    ifs.read((char*)&_accountsIDRecord, sizeof(_accountsIDRecord));
}

bool operator==(const Account& lhs, const Account& rhs)
{
    return lhs.getAccountID() == rhs.getAccountID();
}
