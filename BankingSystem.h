#pragma once
#include "Bank.h"
#include "ThirdPartyEmployee.h"
#include "CommandsCollection.h"
#include <stdlib.h>

enum class UserRole
{
	CLIENT = 1,
	BANK_EMPLOYEE = 2,
	TP_EMPLOYEE = 3
};

class BankingSystem
{
public:

	BankingSystem() = default;
	void signup(const MyString& firstName, const MyString& surname, 
		        const MyString& password, unsigned EGN, unsigned age, UserRole role);
	void signupBankEmployee(const MyString& firstName, const MyString& surname,
						const MyString& password, unsigned EGN, unsigned age, const MyString& bankName);
	void login(unsigned EGN, const MyString& password, UserRole role);
	void create_bank(const MyString bankName);
	void logout();

	void whoami() const;
	void help() const;
	void exit();

	void check_avl(const MyString& bankName, unsigned accountID) const;
	void open(const MyString& bankName);
	void close(const MyString& bankName, unsigned accountID);
	void redeem(const MyString& bankName, unsigned accountID, const char* verificationCode);
	void change(const MyString& newBankName, const MyString& currBankName, unsigned accountID);
	void list(const MyString& bankName) const;
	void messages() const;

	void tasks() const;
	void view(unsigned idx) const;
	void approve(unsigned idx);
	void disapprove(unsigned idx, const MyString& message);
	void validate(unsigned idx);

	void send_check(double sum, const verificationCode code, unsigned EGN);

	bool isTenDigits(unsigned int number);
	int getFileSize(std::ifstream& ifs);

	void saveSystem() const;
	void loadSystem();

private:

	MyVector<Client> _clients;
	MyVector<Bank> _banks;
	MyVector<ThirdPartyEmployee> _tpEmployees;
	Client* _currentC = nullptr;
	BankEmployee* _currentBE = nullptr;
	ThirdPartyEmployee* _currentTPE = nullptr;

	int getBankIdx(const MyString& bankName) const;
	int getClientIdx(unsigned EGN) const;
	int getTPemployeeIdx(unsigned EGN) const;
	int getBEmployeeIdx(unsigned EGN) const;

	void readClients(std::ifstream& ifs);
	void readTPEmployees(std::ifstream& ifs);
	void readBanks(std::ifstream& ifs);
	void readEmployees(std::ifstream& ifs, MyVector<BankEmployee>& employees);
	void readTasks(std::ifstream& ifs, MyVector<Task>& tasks);

	void saveClients(std::ofstream& ofs) const;
	void saveTPEmployees(std::ofstream& ofs) const;
	void saveBanks(std::ofstream& ofs) const;

	

};

