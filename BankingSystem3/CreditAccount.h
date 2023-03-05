#ifndef __CREDIT_ACCOUNT_H__
#define __CREDIT_ACCOUNT_H__

#include "NormalAccount.h"

class CreditAccount : public NormalAccount
{
private:
	int specialRate;
public:
	CreditAccount(int id, String name, int money, int rate, int special) : NormalAccount(id, name, money, rate), specialRate(special)
	{ }
	virtual void Deposit(int money)
	{
		if (money < 0)
			throw MinusException(money);

		NormalAccount::Deposit(money);
		NormalAccount::Deposit(money * (specialRate / 100.0));
	}
};


#endif