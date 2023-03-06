/*
// Account Ŭ���� 
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
		cout << "����ID : " << accID << endl;
		cout << "�̸� : " << cusname << endl;
		cout << "�ܾ� : " << balance << endl;
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
		cout << "���� : ";
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
	cout << "1. ���°���" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}
void MakeAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[���°���]" << endl;
	cout << "����ID : "; cin >> id;
	cout << "�̸� : "; cin >> name;
	cout << "�Աݾ� : "; cin >> balance;

	accAcc[accNum++] = new Account(id, name, balance);
}
void DepositMoney(void)
{
	int id;
	int money;

	cout << "[��  ��]" << endl;
	cout << "����ID : "; cin >> id;
	cout << "�Աݾ� : "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accAcc[i]->GetAccID() == id) {
			accAcc[i]->Deposit(money);
			cout << "�Ա� �Ϸ�" << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}
void WithdrawMoney(void)
{
	int id;
	int money;

	cout << "[��  ��]" << endl;
	cout << "����ID : "; cin >> id;
	cout << "��ݾ� : "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accAcc[i]->GetAccID() == id) {
			if (accAcc[i]->Withdraw(money) == 0)
			{
				cout << "�ܾ� ����" << endl;
				return;
			}
			accAcc[i]->Withdraw(money);
			cout << "��� �Ϸ�" << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
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