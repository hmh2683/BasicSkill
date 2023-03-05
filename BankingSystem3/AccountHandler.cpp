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
	cout << "1. ���°���" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}
void AccountHandler::MakeAccount(void)
{
	int select;

	cout << "[������������]" << endl;
	cout << "1. ���뿹�ݰ��� " << "2. �ſ�ŷڰ���" << endl;
	cout << "���� : "; cin >> select;
	cout << endl;

	if (select == NORMAL)
		MakeNormalAccount();
	else if (select == CREDIT)
		MakeCreditAccount();
	else
		cout << "�߸��� �Է��Դϴ�." << endl;
}

void AccountHandler::MakeNormalAccount(void)
{
	int id;
	String name; // char name[NAME_LEN];
	int balance;
	int interRate;

	cout << "[���°���]" << endl;
	cout << "����ID : "; cin >> id;
	cout << "�̸� : "; cin >> name;
	cout << "�Աݾ� : "; cin >> balance;
	cout << "������ : "; cin >> interRate;
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

	cout << "[���°���]" << endl;
	cout << "����ID : "; cin >> id;
	cout << "�̸� : "; cin >> name;
	cout << "�Աݾ� : "; cin >> balance;
	cout << "������ : "; cin >> interRate;
	cout << "�ſ���(1toA, 2toB, 3toC) : "; cin >> creditLevel;
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
		cout << "�߸��� �Է��Դϴ�." << endl;
	}
}

void AccountHandler::DepositMoney(void)
{
	int id;
	int money;

	cout << "[��  ��]" << endl;
	cout << "����ID : "; cin >> id;

	while (true)
	{
		try
		{
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
			return;
		}
		catch (MinusException& expn)
		{
			expn.ShowExceptionInfo();
			cout << "�Աݾ׸� ���Է��ϼ���." << endl;
		}
	}
}
void AccountHandler::WithdrawMoney(void)
{
	int id;
	int money;

	cout << "[��  ��]" << endl;
	cout << "����ID : "; cin >> id;

	while (true)
	{
		try
		{
			cout << "��ݾ� : "; cin >> money;

			for (int i = 0; i < accNum; i++)
			{
				if (accAcc[i]->GetAccID() == id) {
					accAcc[i]->Withdraw(money);
					cout << "��� �Ϸ�" << endl;
					return;
				}
			}
			cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
			return;
		}
		catch (MinusException& expn)
		{
			expn.ShowExceptionInfo();
			cout << "��ݾ׸� ���Է��ϼ���!" << endl;
		}
		catch (InsuffException& expn)
		{
			expn.ShowExceptionInfo();
			cout << "��ݾ׸� ���Է��ϼ���!" << endl;
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