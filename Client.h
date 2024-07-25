#pragma once
#include <exception>
#include "User.h"
#include "Account.h"
#include "MyVector.hpp"
#include "Check.h"
#include "OpenRequest.h"
#include "CloseRequest.h"
#include "ChangeRequest.h"
#include "SharedPtr.hpp"

class Client : public User
{
public:

	Client() = default;
	Client(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password);

	double check_avl(const MyString& bankName, unsigned accountID) const;
	Request* open(const MyString& bankName);
	Request* close(const MyString& bankName, unsigned accountID);
	void redeem(const MyString& bankName, unsigned accountID, const verificationCode code);
	Request* change(const MyString& newBankName, const MyString& currBankName, unsigned accountID);
	void list(const MyString& bankName) const;
	void messages() const;
	void help() const override;

	void addMessage(const MyString& message);
	void addMessage(MyString&& message);
	void addAccount(const Account& account);
	void removeAccount(const Account& account);
	void removeAccountByID(unsigned id);
	void addCheck(const Check& check);
	void addCheck(Check&& check);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

private:

	MyVector<Account> _accounts;
	MyVector<Check> _checks;
	MyVector<MyString> _messages;

	int getAccountIdx(const MyString& bankName, unsigned accountID) const;

};

