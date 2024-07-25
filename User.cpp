#include "User.h"

User::User(const MyString& firstName, const MyString& surname, unsigned EGN, unsigned age, const MyString& password) : _firstName(firstName),
																														_surname(surname),
																														_EGN(EGN),
																														_age(age),
																														_password(password)
{
}

void User::exit() const
{
	//serialize
}

void User::whoami() const
{
	std::cout << "Name: " << _firstName << " " << _surname << "\n";
	std::cout << "EGN: " << _EGN << "\n";
	std::cout << "Age: " << _age << "\n";
}

void User::help() const
{
	std::cout << "Available commands: \n";
	std::cout << "whoami - view user information\n";
	std::cout << "exit - exit the profile\n";
}

const MyString& User::getFirstName() const
{
	return _firstName;
}

const MyString& User::getSurname() const
{
	return _surname;
}

unsigned User::getAge() const
{
	return _age;
}

unsigned User::getEGN() const
{
	return _EGN;
}

const MyString& User::getPassword() const
{
	return _password;
}

void User::saveToFile(std::ofstream& ofs) const
{
	_firstName.saveToFile(ofs);
	_surname.saveToFile(ofs);
	ofs.write((const char*)&_EGN, sizeof(_EGN));
	ofs.write((const char*)&_age, sizeof(_age));
	_password.saveToFile(ofs);
}

void User::readFromFile(std::ifstream& ifs)
{
	_firstName.readFromFile(ifs);
	_surname.readFromFile(ifs);
	ifs.read((char*)&_EGN, sizeof(_EGN));
	ifs.read((char*)&_age, sizeof(_age));
	_password.readFromFile(ifs);
}
