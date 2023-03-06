/*
// 구조체 및 전역함수 
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

	accAcc[accNum].accID = id;
	accAcc[accNum].balance = balance;
	strcpy(accAcc[accNum].cusname, name);
	accNum++;

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
		if (accAcc[i].accID == id) {
			accAcc[i].balance += money;
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
		if (accAcc[i].accID == id) {
			if (accAcc[i].balance < money)
			{
				cout << "잔액 부족" << endl;
				return;
			}
			accAcc[i].balance -= money;
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
		cout << "계좌ID : " << accAcc[i].accID << endl;
		cout << "이름 : " << accAcc[i].cusname << endl;
		cout << "잔액 : " << accAcc[i].balance << endl;
	}
}
*/