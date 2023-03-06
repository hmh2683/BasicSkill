/*
// Account 클래스 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

void ShowMenu(void);
void MakeAccount(void);
void DepositMoney(void);
void WithdrawMoney(void);
void ShowAllAccInfo(void);

const int NAME_LEN = 20;
enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

class Account
{
private:
	int accID;
	int balance;
	char * cusname;
public:
	Account(int id, char* name, int money) : accID(id), balance(money)
	{ 
		cusname = new char[strlen(name) + 1];
		strcpy(cusname, name);
	}
	Account(const Account& ref) : accID(ref.accID), balance(ref.balance)
	{
		cusname = new char[strlen(ref.cusname) + 1];
		strcpy(cusname, ref.cusname);
	}
	int GetAccID() const { return accID; }
	void Deposit(int money) 
	{ 
		balance += money; 
	}
	int Withdraw(int money)
	{
		if (balance < money)
		{
			return 0;
		}
		balance -= money;
		return money;
	}
	void ShowAccInfo() const
	{
		cout << "계좌ID : " << accID << endl;
		cout << "이름 : " << cusname << endl;
		cout << "잔액 : " << balance << endl;
	}
	~Account()
	{
		delete[] cusname;
	}
};

Account * accAcc[100];
int accNum = 0;

int main(void)
{
	int choice;
	while (1)
	{
		ShowMenu();
		cout << "선택 : ";
		cin >> choice;

		switch (choice)
		{
		case MAKE:
			MakeAccount();
			break;
		case DEPOSIT:
			DepositMoney();
			break;
		case WITHDRAW:
			WithdrawMoney();
			break;
		case INQUIRE:
			ShowAllAccInfo();
			break;
		case EXIT:
			for (int i = 0; i < accNum; i++)
				delete accAcc[i];
			return 0;
		default:
			cout << "Illegal selection..." << endl;
		}
	}
}
void ShowMenu(void)
{
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}
void MakeAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "이름 : "; cin >> name;
	cout << "입금액 : "; cin >> balance;

	accAcc[accNum++] = new Account(id, name, balance);
}
void DepositMoney(void)
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
void WithdrawMoney(void)
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

void ShowAllAccInfo(void)
{
	for (int i = 0; i < accNum; i++)
	{
		accAcc[i]->ShowAccInfo();
		cout << endl;
	}
}
*/