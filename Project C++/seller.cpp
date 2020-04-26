#pragma warning(disable: 4996)
#include "seller.h"

Seller::Seller(const string& username,const string& password, const Address& address) :User(username, password, address) { }

Seller::Seller(ifstream& in) : User(in) { }

Seller::Seller(const Seller& other) :User(other)
{
	*this = other;
}
Seller::~Seller()
{
	int size = _productsArr.size();
	for (int i = 0; i < size; i++)
	{
		delete _productsArr[i]; // delete each pointer
	}
}
const Seller & Seller::operator=(const Seller & other)
{ // overloading operator = 
	if (this != &other)
	{
		User::operator=(other);
		_feedbacksArr = other._feedbacksArr;
		_productsArr = other._productsArr;
	}
	return *this;
}
void Seller::AddProduct(Product& product_to_add)
{ // the function adds an pointer to product to the vector 
	_productsArr.push_back(&product_to_add);
}
void Seller::AddFeedback( Feedback& feedback_to_add)
{ // the function adds feedback to template Array
	_feedbacksArr += &feedback_to_add;
}
 void Seller:: show() const
 { // prints buyers data
	 cout << *this;
 }