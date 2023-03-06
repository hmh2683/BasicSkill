#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

class Account
{
private:
	int accID;
	int balance;
	char* cusName;
public:
	Account(int id, char* name, int money);
	Account(const Account& ref);
	Account& operator=(const Account& ref);

	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
	~Account();
};

#endif 