#ifndef PROJECTCPP1_FEEDBACK_H
#define PROJECTCPP1_FEEDBACK_H

#include "date.h"
#include "buyer.h"

class Feedback
{

private:
	 Date _date;
	 string _text;
	 string _buyer_name;
public:
	Feedback(const string& buyer_name, const string& text, Date &date);
	Feedback(const Feedback& other);

	//set functions
	void setText(const string&text);
	void setBuyerName(const string& name);

	//get functions
	const Date& getDate() const { return _date; }
	Date& getDate() { return _date; }
	inline const string& getText()const { return _text; }
	inline const string&  getBuyerName()const { return _buyer_name; }

	//operators
	const Feedback& operator=(const Feedback& other);
};


#endif //PROJECTCPP1_FEEDBACK_H