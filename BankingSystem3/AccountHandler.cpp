#include "BankingCommon.h"
#include "AccountHandler.h"
#include "Account.h"
#include "NormalAccount.h"
#include "CreditAccount.h"
#include "String.h"
#include "AccountException.h"

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
	String name; // char name[NAME_LEN];
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
	String name; // char name[NAME_LEN];
	int balance;
	int interRate;
	int creditLevel;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID : "; cin >> id;
	cout << "이름 : "; cin >> name;
	cout << "입금액 : "; cin >> balance;
	cout << "이자율 : "; cin >> interRate;
	cout << "신용등급(1toA, 2toB, 3toC) : "; cin >> creditLevel;
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

	while (true)
	{
		try
		{
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
			return;
		}
		catch (MinusException& expn)
		{
			expn.ShowExceptionInfo();
			cout << "입금액만 재입력하세요." << endl;
		}
	}
}
void AccountHandler::WithdrawMoney(void)
{
	int id;
	int money;

	cout << "[출  금]" << endl;
	cout << "계좌ID : "; cin >> id;

	while (true)
	{
		try
		{
			cout << "출금액 : "; cin >> money;

			for (int i = 0; i < accNum; i++)
			{
				if (accAcc[i]->GetAccID() == id) {
					accAcc[i]->Withdraw(money);
					cout << "출금 완료" << endl;
					return;
				}
			}
			cout << "유효하지 않은 ID 입니다." << endl << endl;
			return;
		}
		catch (MinusException& expn)
		{
			expn.ShowExceptionInfo();
			cout << "출금액만 재입력하세요!" << endl;
		}
		catch (InsuffException& expn)
		{
			expn.ShowExceptionInfo();
			cout << "출금액만 재입력하세요!" << endl;
		}
	}
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