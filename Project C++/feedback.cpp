#pragma warning(disable: 4996)
#include "feedback.h"

Feedback::Feedback(const string& buyer_name, const string& text, Date &date) :_date(date)
{
	setBuyerName(buyer_name);
	setText(text);
}
Feedback::Feedback(const Feedback& other) : _date(other._date)
{
	*this = other;
}
const Feedback& Feedback::operator=(const Feedback& other)
{ // overloading operator =
	if (this != &other)
	{
		setBuyerName(other._buyer_name);
		_text = other._text;
	}
	return *this;
}
void Feedback::setText(const string& text)
{
	_text=text; //copy the given string
}
void Feedback::setBuyerName(const string& name)
{
	_buyer_name = name;
}