// NormalClass CreditClass 상속
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

const int NAME_LEN = 20;

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };
enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL_C = 2 };
enum { NORMAL = 1, CREDIT = 2 };

class Account
{
private:
	int accID;
	int balance;
	char* cusname;
public:
	Account(int id, char* name, int money);
	Account(const Account& ref);
	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
	~Account();
};

Account::Account(int id, char* name, int money) : accID(id), balance(money)
{
	cusname = new char[strlen(name) + 1];
	strcpy(cusname, name);
}
Account::Account(const Account& ref) : accID(ref.accID), balance(ref.balance)
{
	cusname = new char[strlen(ref.cusname) + 1];
	strcpy(cusname, ref.cusname);
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)
{
	balance += money;
}

int Account::Withdraw(int money)
{
	if (balance < money)
	{
		return 0;
	}
	balance -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "계좌ID : " << accID << endl;
	cout << "이름 : " << cusname << endl;
	cout << "잔액 : " << balance << endl;
}

Account::~Account()
{
	delete[] cusname;
}

class NormalAccount : public Account
{
private:
	int interRate;
public:
	NormalAccount(int id, char* name, int money, int rate) : Account(id, name, money), interRate(rate)
	{ }
	virtual void Deposit(int money)
	{
		Account::Deposit(money);
		Account::Deposit(money * (interRate / 100.0));
	}
};

class CreditAccount : public NormalAccount
{
private:
	int specialRate;
public:
	CreditAccount(int id, char* name, int money, int rate, int special) : NormalAccount(id, name, money, rate), specialRate(special)
	{ }
	virtual void Deposit(int money)
	{
		NormalAccount::Deposit(money);
		NormalAccount::Deposit(money * (specialRate / 100.0));
	}
};

class AccountHandler
{
private:
	Account* accAcc[100];
	int accNum;
public:
	AccountHandler();
	void ShowMenu(void) const;
	void MakeAccount(void);
	void DepositMoney(void);
	void WithdrawMoney(void);
	void ShowAllAccInfo(void) const;
	~AccountHandler();
protected:
	void MakeNormalAccount(void);
	void MakeCreditAccount(void);
};

AccountHandler::AccountHandler() : accNum(0)
{ }

void AccountHandler::ShowMenu(void) const
{
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}
void AccountHandler::MakeAccount(void)
{
	int select;

	cout << "[계좌종류선택]" << endl;
	cout << "1. 보통예금계좌 " << "2. 신용신뢰계좌" << endl;
	cout << "선택 : "; cin >> select;
	cout << endl;

	if (select == NORMAL)
		MakeNormalAccount();
	else if (select == CREDIT)
		MakeCreditAccount();
	else
		cout << "잘못된 입력입니다." << endl;
}

void AccountHandler::MakeNormalAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "이름 : "; cin >> name;
	cout << "입금액 : "; cin >> balance;
	cout << "이자율 : "; cin >> interRate;
	cout << endl;

	accAcc[accNum++] = new NormalAccount(id, name, balance, interRate);
}
void AccountHandler::MakeCreditAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;
	int creditLevel;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "이름 : "; cin >> name;
	cout << "입금액 : "; cin >> balance;
	cout << "이자율 : "; cin >> interRate;
	cout << "신용등급(1toA, 2toB, 3toC : "; cin >> creditLevel;
	cout << endl;

	switch (creditLevel)
	{
	case 1:
		accAcc[accNum++] = new CreditAccount(id, name, balance, interRate, LEVEL_A);
		break;
	case 2:
		accAcc[accNum++] = new CreditAccount(id, name, balance, interRate, LEVEL_B);
		break;
	case 3:
		accAcc[accNum++] = new CreditAccount(id, name, balance, interRate, LEVEL_C);
		break;
	default:
		cout << "잘못된 입력입니다." << endl;
	}
}

void AccountHandler::DepositMoney(void)
{
	int id;
	int money;

	cout << "[입  금]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "입금액 : "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accAcc[i]->GetAccID() == id) {
			accAcc[i]->Deposit(money);
			cout << "입금 완료" << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
}
void AccountHandler::WithdrawMoney(void)
{
	int id;
	int money;

	cout << "[출  금]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "출금액 : "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accAcc[i]->GetAccID() == id) {
			if (accAcc[i]->Withdraw(money) == 0)
			{
				cout << "잔액 부족" << endl;
				return;
			}
			accAcc[i]->Withdraw(money);
			cout << "출금 완료" << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
}

void AccountHandler::ShowAllAccInfo(void) const
{
	for (int i = 0; i < accNum; i++)
	{
		accAcc[i]->ShowAccInfo();
		cout << endl;
	}
}

AccountHandler::~AccountHandler()
{
	for (int i = 0; i < accNum; i++)
	{
		delete accAcc[i];
	}
}

int main(void)
{
	AccountHandler manager;
	int choice;
	while (1)
	{
		manager.ShowMenu();
		cout << "선택 : ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case MAKE:
			manager.MakeAccount();
			break;
		case DEPOSIT:
			manager.DepositMoney();
			break;
		case WITHDRAW:
			manager.WithdrawMoney();
			break;
		case INQUIRE:
			manager.ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout << "잘못된 입력입니다." << endl;
		}
	}
	return 0;
}
