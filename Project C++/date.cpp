#include "date.h"

Date::Date(int day,int month,int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}
bool Date::setDay(int day)
{
	if (day < 1 || day>31)
		return false;
	else
	{
		this->_day = day;
		return true;
	}
}
bool Date::setMonth(int month)
{
	if (month < 1 || month>12)
		return false;
	else
	{
		this->_month = month;
		return true;
	}
}
bool Date::setYear(int year)
{
	if (year < 2019 )
		return false;
	else
	{
		this->_year = year;
		return true;
	}
}
void Date::print()
{
	cout << getDay() << "/" << getMonth() << "/" << getYear();
}