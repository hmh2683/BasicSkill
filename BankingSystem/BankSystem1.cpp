/*
// ����ü �� �����Լ� 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

const int NAME_LEN = 20;

void ShowMenu(void);
void MakeAccount(void);
void DepositMoney(void);
void WithdrawMoney(void);
void ShowAllAccInfo(void);

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

typedef struct
{
	int accID;
	int balance;
	char cusname[NAME_LEN];
}Account;

Account accAcc[100];
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

	accAcc[accNum].accID = id;
	accAcc[accNum].balance = balance;
	strcpy(accAcc[accNum].cusname, name);
	accNum++;

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
		if (accAcc[i].accID == id) {
			accAcc[i].balance += money;
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
		if (accAcc[i].accID == id) {
			if (accAcc[i].balance < money)
			{
				cout << "�ܾ� ����" << endl;
				return;
			}
			accAcc[i].balance -= money;
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
		cout << "����ID : " << accAcc[i].accID << endl;
		cout << "�̸� : " << accAcc[i].cusname << endl;
		cout << "�ܾ� : " << accAcc[i].balance << endl;
	}
}
*/