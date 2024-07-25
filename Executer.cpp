#include "Executer.h"

void Executer::run()
{
	BankingSystem bs;
	bs.loadSystem();

	MyString command;
	
	std::cout << "Welcome to BankingSystem! You can start by creating a bank (create_bank command) or signing up (signup command). If you have an account already you can log in (login command). \n";
	std::cout << '\n';
	while (true)
	{
		std::cout << "Please enter a command:\n";
		std::cin >> command;

		try
		{
			if (command == "create_bank")
			{
				MyString bankName;
				std::cout << "Enter bank name: \n";
				std::cin >> bankName;

				bs.create_bank(bankName);
				std::cout << "Bank created a successfully!\n";
			}

			else if (command == "signup")
			{
				MyString firstName, surname, password;
				unsigned EGN, age;
				UserRole role;
				int temp;

				std::cout << "What do you want to sign up as: 1 - Client, 2 - Bank employee, 3 - Third party employee. Please enter a number 1-3.\n";
				std::cin >> temp;
				role = static_cast<UserRole>(temp);

				std::cout << "Enter your first name and surname.\n";
				std::cin >> firstName >> surname;
				std::cout << "Enter your age and EGN.\n";
				std::cin >> age >> EGN;
				if (!bs.isTenDigits(EGN))
				{
					throw std::exception("Incorrect EGN. Try again.");
				}

				std::cout << "Enter your password.\n";
				std::cin >> password;

				if (role == UserRole::BANK_EMPLOYEE)
				{
					MyString bankName;
					std::cout << "Enter your bank's name.\n";
					std::cin >> bankName;
					bs.signupBankEmployee(firstName, surname, password, EGN, age, bankName);
				}
				else
				{
					bs.signup(firstName, surname, password, EGN, age, role);
				}

				std::cout << "Signed up successfully!\n";
				system("CLS");
			
			}

			else if (command == "login")
			{
				MyString password;
				unsigned EGN;
				int temp;
				UserRole role;

				std::cout << "Enter your role: 1 - Client, 2 - Bank employee, 3 - Third party employee.\n";
				std::cin >> temp;
				role = static_cast<UserRole>(temp);

				std::cout << "Enter your EGN.\n";
				std::cin >> EGN;
				if (!bs.isTenDigits(EGN))
				{
					throw std::exception("Incorrect EGN. Try again.");
				}

				std::cout << "Enter your password.\n";
				std::cin >> password;

				bs.login(EGN, password, role);
				std::cout << "Logged in successfully!\n";
			}

			else if (command == "logout")
			{
				bs.logout();
			}

			else if (command == "whoami")
			{

				bs.whoami();
			}

			else if (command == "help")
			{
				bs.help();
			}

			else if (command == "exit")
			{
				bs.exit();
				break;
			}

			else if (command == "check_avl")
			{
				MyString bankName;
				unsigned accountId;

				std::cout << "Enter bank name.\n";
				std::cin >> bankName;
				std::cout << "Enter account ID.\n";
				std::cin >> accountId;

				bs.check_avl(bankName, accountId);
			}

			else if (command == "open")
			{
				MyString bankName;
				std::cout << "Enter bank name.\n";
				std::cin >> bankName;

				bs.open(bankName);
				std::cout << "Request sent out successfully!\n";
			}

			else if (command == "close")
			{
				MyString bankName;
				unsigned accountId;

				std::cout << "Enter bank name.\n";
				std::cin >> bankName;
				std::cout << "Enter account ID.\n";
				std::cin >> accountId;

				bs.close(bankName, accountId);
				std::cout << "Request sent out successfully!\n";

			}

			else if (command == "redeem")
			{
				MyString bankName;
				unsigned accountId;
				verificationCode code;

				std::cout << "Enter bank name.\n";
				std::cin >> bankName;
				std::cout << "Enter account ID.\n";
				std::cin >> accountId;
				std::cout << "Enter your verification code.\n";
				std::cin >> code;

				bs.redeem(bankName, accountId, code);
				std::cout << "Request sent out successfully!\n";

			}

			else if (command == "change")
			{
				MyString newBankName, currBankName;
				unsigned accountId;

				std::cout << "Enter the name of the bank you want to change to.\n";
				std::cin >> newBankName;
				std::cout << "Enter the name of the bank you are changing from.\n";
				std::cin >> currBankName;
				std::cout << "Enter account ID.\n";
				std::cin >> accountId;

				bs.change(newBankName, currBankName, accountId);
				std::cout << "Request sent out successfully!\n";

			}

			else if (command == "list")
			{
				MyString bankName;
				std::cout << "Enter bank name.\n";
				std::cin >> bankName;

				bs.list(bankName);
			}

			else if (command == "messages")
			{
				bs.messages();
			}

			else if (command == "tasks")
			{
				bs.tasks();
			}

			else if (command == "view")
			{
				unsigned id;
				std::cout << "Enter task ID.\n";
				std::cin >> id;

				bs.view(id);
			}

			else if (command == "approve")
			{
				unsigned id;
				std::cout << "Enter task ID.\n";
				std::cin >> id;

				bs.approve(id);
				std::cout << "Task approved successfully.\n";
			}

			else if (command == "disapprove")
			{
				MyString message;
				static const unsigned buffSize = 256;
				char buff[buffSize];
				unsigned id;
				std::cout << "Enter task ID.\n";
				std::cin >> id;
				std::cout << "Enter reasoning.\n";
				std::cin.getline(buff, buffSize);
				message = buff;

				bs.disapprove(id, message);
				std::cout << "Task disapproved successfully.\n";
			}

			else if (command == "validate")
			{
				unsigned id;
				std::cout << "Enter task ID.\n";
				std::cin >> id;

				bs.validate(id);
				std::cout << "Task sent out for validation successfully.\n";
			}

			else if (command == "send_check")
			{
				double sum;
				verificationCode code;
				unsigned EGN;

				std::cout << "Enter the sum of the check.\n";
				std::cin >> sum;
				std::cout << "Enter the verification code.\n";
				std::cin >> code;
				std::cout << "Enter the EGN of the reciever.\n";
				std::cin >> EGN;

				bs.send_check(sum, code, EGN);
				std::cout << "Check sent out successfully.\n";
			}

			else 
			{
				throw std::invalid_argument("Invalid command");
				continue;
			}
		}

		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << '\n';
		}

		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << '\n';
		}

		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}

		catch (...)
		{
			std::cout << "Unexpected error!\n";
		}

	}
	
}
