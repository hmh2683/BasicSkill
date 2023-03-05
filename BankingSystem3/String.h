#ifndef __STRING_H__
#define __STRING_H__

#include "BankingCommon.h"

class String
{
private:
	char* str;
	int len;
public:
	String();
	String(const char* s);
	String(const String& s);
	~String();

	String& operator=(const String& s);
	String& operator+=(const String& s);
	bool operator==(const String& s);
	String operator+(const String& s);

	friend ostream& operator<< (ostream& os, const String& s);
	friend istream& operator>> (istream& is, String& s);
};

#endif 
