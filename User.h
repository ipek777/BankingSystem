#pragma once
#include "MyString.h"

class User
{
public:
	User() = default;
	User(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password);
	void exit() const;
	void whoami() const;
	virtual void help() const;

	const MyString& getFirstName() const;
	const MyString& getSurname() const;
	unsigned getAge() const;
	unsigned getEGN() const;
	const MyString& getPassword() const;

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

protected:
	MyString _firstName;
	MyString _surname;
	unsigned _EGN = 0;
	unsigned _age = 0;
	MyString _password;

};

