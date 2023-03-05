#include "BankingCommon.h"
#include "Account.h"
#include "AccountException.h"

Account::Account(int id, String name, int money) : accID(id), balance(money)
{
	//cusName = new char[strlen(name) + 1];
	//strcpy(cusName, name);
	cusName = name;
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)
{
	if (money < 0)
		throw MinusException(money);

	balance += money;
}

int Account::Withdraw(int money)
{
	if (money < 0)
		throw MinusException(money);

	if (balance < money)
		throw InsuffException(balance, money);

	balance -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "°èÁÂID : " << accID << endl;
	cout << "ÀÌ¸§ : " << cusName << endl;
	cout << "ÀÜ¾× : " << balance << endl;
}

/*
Account::Account(const Account& ref) : accID(ref.accID), balance(ref.balance)
{
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy(cusName, ref.cusName);
}
Account& Account::operator=(const Account& ref)
{
	accID = ref.accID;
	balance = ref.balance;

	delete[] cusName;
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy(cusName, ref.cusName);
	return *this;
}

Account::~Account()
{
	delete[] cusName;
}
*/