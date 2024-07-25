#include "BankingSystem.h"

void BankingSystem::signup(const MyString& firstName, const MyString& surname, const MyString& password, unsigned EGN, unsigned age, UserRole role)
{
    if (role == UserRole::CLIENT)
    {
        Client client(firstName, surname, EGN, age, password);
        _clients.push_back(client);
    }
    else
    {
        ThirdPartyEmployee tpEmployee(firstName, surname, EGN, age, password);
        _tpEmployees.push_back(tpEmployee);
    }
}

void BankingSystem::signupBankEmployee(const MyString& firstName, const MyString& surname, const MyString& password, unsigned EGN, unsigned age, const MyString& bankName)
{
    BankEmployee bEmployee(firstName, surname, EGN, age, password, bankName);
    int idx = getBankIdx(bankName);

    if (idx >= 0)
    {
        _banks[idx].addEmployee(bEmployee);
    }
    else
    {
        throw std::exception("No such bank exists");
    }

}

void BankingSystem::login(unsigned EGN, const MyString& password, UserRole role)
{
    switch (role)
    {
    case UserRole::CLIENT:
    {
        int idx = getClientIdx(EGN);
        if (idx >= 0 && _clients[idx].getPassword() == password)
        {
            _currentC = &_clients[idx];
            return;
        }
        else
        {
            throw std::exception("No such client exists");
        }
    }
    case UserRole::BANK_EMPLOYEE:
    {
        int idx = getBEmployeeIdx(EGN); 
        if (idx >= 0)
        {
            int employeeIdx = _banks[idx].getEmployeeIdx(EGN);
            _currentBE = &_banks[idx].getEmployee(employeeIdx);
            return;
        }
        else
        {
            throw std::exception("No such employee exists");
        }
    }
    case UserRole::TP_EMPLOYEE:
    {
        int idx = getTPemployeeIdx(EGN);
        if (idx >= 0)
        {
            _currentTPE = &_tpEmployees[idx];
            return;
        }
        else
        {
            throw std::exception("No such employee exists");
        }
    }
    default:
        break;
    }

}

int BankingSystem::getBankIdx(const MyString& bankName) const
{
    int idx = -1;
    for (size_t i = 0; i < _banks.size(); i++)
    {
        if (_banks[i].getName() == bankName)
        {
            idx = i;
            break;
        }
    }
    return idx;
}

int BankingSystem::getClientIdx(unsigned EGN) const
{
    int idx = -1;
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i].getEGN() == EGN)
        { 
            idx = i;
            break;
        }
    }
    return idx;
}

int BankingSystem::getTPemployeeIdx(unsigned EGN) const
{
    int idx = -1;
    for (size_t i = 0; i < _tpEmployees.size(); i++)
    {
        if (_tpEmployees[i].getEGN() == EGN)
        {
            idx = i;
            break;
        }
    }
    return idx;
}

int BankingSystem::getBEmployeeIdx(unsigned EGN) const
{
    int idx = -1;
    for (size_t i = 0; i < _banks.size(); i++)
    {
        int employeeIdx = _banks[i].getEmployeeIdx(EGN);
        if (employeeIdx >= 0)
        {
            idx = i;
            break;
        }
    }
    return idx;
}

void BankingSystem::readClients(std::ifstream& ifs)
{
    int cSize;
    ifs.read((char*)&cSize, sizeof(cSize));
    if (cSize != 0)
    {
        _clients = MyVector<Client>(cSize);
        for (size_t i = 0; i < cSize; i++)
        {
            _clients[i].readFromFile(ifs);
        }
    }
   
}

void BankingSystem::readTPEmployees(std::ifstream& ifs)
{
    int tpeSize;
    ifs.read((char*)&tpeSize, sizeof(tpeSize));
    if (tpeSize != 0)
    {
        _tpEmployees = MyVector<ThirdPartyEmployee>(tpeSize);
        for (size_t i = 0; i < tpeSize; i++)
        {
            _tpEmployees[i].readFromFile(ifs);
        }
    }
    
}

void BankingSystem::readBanks(std::ifstream& ifs)
{
    int bSize;
    ifs.read((char*)&bSize, sizeof(bSize));

    if (bSize != 0)
    {
        _banks = MyVector<Bank>(bSize);

        for (size_t i = 0; i < bSize; i++)
        {
            MyString name;
            name.readFromFile(ifs);

            int eSize;
            ifs.read((char*)&eSize, sizeof(eSize));
            if (eSize != 0)
            {
                MyVector<BankEmployee> vec(eSize);
                readEmployees(ifs, vec);
                _banks[i].setFromFile(name, vec);
            }
            else
            {
                MyVector<BankEmployee> vec;
                _banks[i].setFromFile(name, vec); 
            }

        }
    }
    
}

void BankingSystem::readEmployees(std::ifstream& ifs, MyVector<BankEmployee>& employees)
{
    for (size_t i = 0; i < employees.size(); i++)
    {
        User user;
        user.readFromFile(ifs);
        MyString bankName;
        bankName.readFromFile(ifs);
        
        int tSize;
        ifs.read((char*)&tSize, sizeof(tSize));
        if (tSize != 0)
        {
            MyVector<Task> vec(tSize);
            readTasks(ifs, vec);

            employees[i].setFromFile(user, bankName, vec);
        }
        else
        {
            MyVector<Task> vec;
            employees[i].setFromFile(user, bankName, vec);
        }
    }
}

void BankingSystem::readTasks(std::ifstream& ifs, MyVector<Task>& tasks)
{
    for (size_t i = 0; i < tasks.size(); i++)
    {
        RequestType type;
        Client temp;
        ifs.read((char*)&type, sizeof(type));
        temp.readFromFile(ifs);

        int idx = getClientIdx(temp.getEGN());
        Client& issuer = _clients[idx];
        tasks[i].readFromFile(ifs, type, issuer);
    }
}

void BankingSystem::saveClients(std::ofstream& ofs) const
{
    int cSize = _clients.size();
    ofs.write((const char*)&cSize, sizeof(cSize));

    for (size_t i = 0; i < cSize; i++)
    {
        _clients[i].saveToFile(ofs);
    }
}

void BankingSystem::saveTPEmployees(std::ofstream& ofs) const
{
    int tpSize = _tpEmployees.size();
    ofs.write((const char*)&tpSize, sizeof(tpSize));

    for (size_t i = 0; i < tpSize; i++)
    {
        _tpEmployees[i].saveToFile(ofs);
    }
}

void BankingSystem::saveBanks(std::ofstream& ofs) const
{
    int bSize = _banks.size();
    ofs.write((const char*)&bSize, sizeof(bSize));

    for (size_t i = 0; i < bSize; i++)
    {
        _banks[i].saveToFile(ofs);
    }
}

void BankingSystem::saveSystem() const
{
    std::ofstream ofs("BankingSystem.dat", std::ios::binary);
    if (!ofs.is_open())
    {
        throw std::runtime_error("Cannot open file for writing.");
    }

    saveClients(ofs);
    saveTPEmployees(ofs);
    saveBanks(ofs);

    ofs.close();
}

void BankingSystem::loadSystem()
{
    std::ifstream ifs("BankingSystem.dat", std::ios::binary);
    if (!ifs.is_open())
    {
        throw std::runtime_error("Cannot open file for reading.");
    }

    if (!getFileSize(ifs))
    {
        return;
    }

    readClients(ifs);
    readTPEmployees(ifs);
    readBanks(ifs);

    ifs.close();
}

int BankingSystem::getFileSize(std::ifstream& ifs)
{
    size_t currentIndex = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(currentIndex);
    return size;
}

void BankingSystem::create_bank(const MyString bankName)
{
    int idx = getBankIdx(bankName);
    if (idx == -1)
    {
        Bank bank(bankName);
        _banks.push_back(bank);
    }
    else
    {
        throw std::exception("This bank already exists");
    }
}

void BankingSystem::logout()
{
    if (_currentC)
    {
        _currentC = nullptr;
        system("CLS");
    }

    else if (_currentBE)
    {
        _currentBE = nullptr;
        system("CLS");
    }

    else if (_currentTPE)
    {
        _currentTPE = nullptr;
        system("CLS");
    }

    else
    {
        throw std::runtime_error("No one is logged in.");
    }
}

void BankingSystem::whoami() const
{
    if (_currentC)
    {
        _currentC->whoami();
    }

    else if (_currentBE)
    {
        _currentBE->whoami();
    }

    else if (_currentTPE)
    {
        _currentTPE->whoami();
    }

    else
    {
        throw std::runtime_error("No one is logged in.");
    }

}

void BankingSystem::help() const
{
    if (_currentC)
    {
        _currentC->help();
    }

    else if (_currentBE)
    {
        _currentBE->help();
    }

    else if (_currentTPE)
    {
        _currentTPE->help();
    }

    else
    {
        throw std::runtime_error("No one is logged in.");
    }
}

void BankingSystem::exit()
{
    saveSystem();
}

void BankingSystem::check_avl(const MyString& bankName, unsigned accountID) const
{
    if (!_currentC)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    CheckAvlCommand c(*_currentC, bankName, accountID);
    c.execute();
}

void BankingSystem::open(const MyString& bankName)  
{
    if (!_currentC)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    int idx = getBankIdx(bankName);
    OpenCommand c(*_currentC, bankName, _banks[idx]);
    c.execute();
}

void BankingSystem::close(const MyString& bankName, unsigned accountID)
{
    if (!_currentC)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    int idx = getBankIdx(bankName);
    CloseCommand c(*_currentC, bankName, accountID, _banks[idx]);
    c.execute();
}

void BankingSystem::redeem(const MyString& bankName, unsigned accountID, const char* verificationCode)
{
    if (!_currentC)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    RedeemCommand c(*_currentC, bankName, accountID, verificationCode);
    c.execute();
}

void BankingSystem::change(const MyString& newBankName, const MyString& currBankName, unsigned accountID)
{
    if (!_currentC)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    int idx = getBankIdx(newBankName);
    ChangeCommand c(*_currentC, newBankName, currBankName, accountID, _banks[idx]);
    c.execute();
}

void BankingSystem::list(const MyString& bankName) const
{
    if (!_currentC)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    ListCommand c(*_currentC, bankName);
    c.execute();
}

void BankingSystem::messages() const
{
    if (!_currentC)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    MessagesCommand c(*_currentC);
    c.execute();
}

void BankingSystem::tasks() const
{
    if (!_currentBE)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    TasksCommand c(*_currentBE);
    c.execute();
}

void BankingSystem::view(unsigned idx) const
{
    if (!_currentBE)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    ViewCommand c(*_currentBE, idx);
    c.execute();
}

void BankingSystem::approve(unsigned idx)
{
    if (!_currentBE)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    ApproveCommand c(*_currentBE, idx);
    c.execute();
}

void BankingSystem::disapprove(unsigned idx, const MyString& message)
{
    if (!_currentBE)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    DisapproveCommand c(*_currentBE, idx, message);
    c.execute();
}

void BankingSystem::validate(unsigned idx)
{
    if (!_currentBE)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    ChangeRequest* changeRequest = dynamic_cast<ChangeRequest*>(_currentBE->getTask(idx)->getRequest().get());
    if (!changeRequest)
    {
        throw std::runtime_error("Invalid request type for CHANGE operation.");
    }

    MyString currentBank = changeRequest->getCurrentBankName();
    int bankIdx = getBankIdx(currentBank);
    if (idx < 0)
    {
        throw std::exception("No such bank exists");
    }

    ValidateCommand c(*_currentBE, idx, _banks[bankIdx]);
    c.execute();
}

void BankingSystem::send_check(double sum, const verificationCode code, unsigned EGN)
{

    if (!_currentTPE)
    {
        throw std::runtime_error("Command cannot be executed!");
    }

    int idx = getClientIdx(EGN);
    if (idx < 0)
    {
        throw std::exception("No such client exists.");
    }

    SendCheckCommand c(*_currentTPE, sum, code, EGN, _clients[idx]);
    c.execute();
}

bool BankingSystem::isTenDigits(unsigned int number) {
    int digitCount = 0;

    while (number != 0) {
        number /= 10;
        digitCount++;
    }

    return digitCount == 10;
}