#ifndef __DATE_H
#define  __DATE_H
#include "buyer.h"

class Date 
{
private:
	int _day;
	int _month;
	int _year;
public:
	Date(int day,int month,int year);

	// set functions
	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);
	
	// get functions
	inline int getDay() const { return _day; }
	inline int getMonth() const { return _month; }
	inline int getYear() const { return _year; }

	void print();
};
#endif // !__DATE_H
