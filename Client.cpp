#include "Client.h"

Client::Client(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password) : User(firstName, surname, EGN, age, password)
{
}

double Client::check_avl(const MyString& bankName, unsigned accountID) const
{
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i].getBankName() == bankName && _accounts[i].getAccountID() == accountID)
		{
			return _accounts[i].getBalance();
		}
	}
	throw std::exception("No such account exists!");
}

Request* Client::open(const MyString& bankName)
{
	OpenRequest* ptr = new OpenRequest(bankName, *this);
	return ptr;
}

Request* Client::close(const MyString& bankName, unsigned accountID)
{
	CloseRequest* ptr = new CloseRequest(bankName, accountID, *this);
	return ptr;
}

void Client::redeem(const MyString& bankName, unsigned accountID, const verificationCode code) 
{ 
	int idx = getAccountIdx(bankName, accountID);
	if (idx < 0)
	{
		throw std::invalid_argument("No such account exists");
	}

	for (size_t i = 0; i < _checks.size(); i++)
	{
		if (!strcmp(_checks[i].getVerificationCode(), code))
		{
			if (_checks[i].IsRedeemed())
			{
				throw std::exception("Check has been redeemed already");
			}

			_checks[i].setIsRedeemed(true);
			_accounts[idx].setBalance(_checks[i].getSum());
			return;
		}
	}
}

Request* Client::change(const MyString& newBankName, const MyString& currBankName, unsigned accountID)
{
	ChangeRequest* ptr = new ChangeRequest(newBankName, currBankName, accountID, *this);
	return ptr; 
}

void Client::list(const MyString& bankName) const
{
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (!strcmp(_accounts[i].getBankName().c_str(), bankName.c_str()))
		{
			_accounts[i].print();
		}
	}
}

void Client::messages() const
{
	for (size_t i = 0; i < _messages.size(); i++)
	{
		std::cout << _messages[i] << '\n';
	}
}

void Client::help() const
{
	std::cout << "check_avl - check your balance for a particular account\n";
	std::cout << "open - open a new account\n";
	std::cout << "close - close an account\n";
	std::cout << "change - change an account to another bank\n";
	std::cout << "redeem - redeem a check\n";
	std::cout << "list - list all accounts in a certain bank\n";
	std::cout << "messages - view all of your messages\n";
}

void Client::addMessage(const MyString& message)
{
	_messages.push_back(message);
}

void Client::addMessage(MyString&& message)
{
	_messages.push_back(std::move(message));
}

void Client::addAccount(const Account& account)
{
	_accounts.push_back(account);
	MyString id(account.getAccountID()); 
	MyString message = "Added new account with id #" + id;
	addMessage(message);
}

void Client::removeAccount(const Account& account)
{
	int idx = _accounts.find(account);
	if (idx < 0)
	{
		throw std::invalid_argument("No such account exists!");
	}
	_accounts.erase(idx);
}

void Client::removeAccountByID(unsigned id)
{
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i].getAccountID() == id) 
		{
			_accounts.erase(i);
			return;
		}
	}
}

void Client::addCheck(const Check& check)
{
	_checks.push_back(check);
}

void Client::addCheck(Check&& check)
{
	_checks.push_back(std::move(check));
}

void Client::saveToFile(std::ofstream& ofs) const
{
	User::saveToFile(ofs);
	unsigned aSize = _accounts.size();
	unsigned cSize = _checks.size();
	unsigned mSize = _messages.size();

	ofs.write((const char*)&aSize, sizeof(aSize));
	for (size_t i = 0; i < aSize; i++)
	{
		_accounts[i].saveToFile(ofs);
	}

	ofs.write((const char*)&cSize, sizeof(cSize));
	for (size_t i = 0; i < cSize; i++)
	{
		_checks[i].saveToFile(ofs);
	}

	ofs.write((const char*)&mSize, sizeof(mSize));
	for (size_t i = 0; i < mSize; i++)
	{
		_messages[i].saveToFile(ofs);
	}
}

void Client::readFromFile(std::ifstream& ifs)
{
	_firstName.readFromFile(ifs);
	_surname.readFromFile(ifs);
	ifs.read((char*)&_EGN, sizeof(_EGN));
	ifs.read((char*)&_age, sizeof(_age));
	_password.readFromFile(ifs);
	unsigned aSize, cSize, mSize;
	
	ifs.read((char*)&aSize, sizeof(aSize));
	if (aSize != 0)
	{
		_accounts = MyVector<Account>(aSize);
		for (size_t i = 0; i < aSize; i++)
		{
			_accounts[i].readFromFile(ifs);
		}
	}
	

	ifs.read((char*)&cSize, sizeof(cSize));
	if (cSize != 0)
	{
		_checks = MyVector<Check>(cSize);
		for (size_t i = 0; i < cSize; i++)
		{
			_checks[i].readFromFile(ifs);
		}
	}
	

	ifs.read((char*)&mSize, sizeof(mSize));
	if (mSize != 0)
	{
		_messages = MyVector<MyString>(mSize);
		for (size_t i = 0; i < mSize; i++)
		{
			_messages[i].readFromFile(ifs);
		}
	}
	
}

int Client::getAccountIdx(const MyString& bankName, unsigned accountID) const
{
	int idx = -1;
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i].getAccountID() == accountID && _accounts[i].getBankName() == bankName)
		{
			idx = i;
			break;
		}
	}
	return idx;
}




