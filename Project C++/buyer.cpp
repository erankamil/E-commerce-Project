#pragma warning(disable: 4996)
#include "buyer.h"
#include <iostream>
#include <fstream>

Buyer::Buyer(const string& username, const string& password, const Address& address) :User(username, password, address) {};

Buyer::Buyer(ifstream& in) :User(in)
{

}
Buyer::Buyer(const Buyer& other) :User(other),_order(other._order),_purchaseHistory(other._purchaseHistory),_cart(other._cart)
{
	*this = other;
};
void Buyer::addToCart(Product& product_to_add)
{// the function gets a product by ref and adds it to the cart
	_cart.addProduct(product_to_add);
}
void Buyer::addProudctToOrder( Product& product_to_add)
{ // the function gets a product by ref and adds it to the order
	_order.addProduct(product_to_add);
}
void Buyer::saveOrder()
{ // the function saves the current order to the purchase history array and reset the cart and the order
	_purchaseHistory.saveOrder(_order);
	_cart.reset();
	_order.reset();
}
const string& Buyer::operator>(const Buyer& other)
{ // overloading operator > , returns the name of the buyer with the bigger total cost of cart
	if (this->getCart().getTotalPrice() > other.getCart().getTotalPrice())
		return this->getUserName();
	else
		return other.getUserName();
}
const Buyer & Buyer::operator=(const Buyer & other)
{ // overloading operator=
	if (this != &other)
	{
		User::operator=(other);
		this->_cart = other._cart;
		this->_purchaseHistory = other._purchaseHistory;
	}
	return *this;
}
istream& operator>>(istream& in, const Buyer& buyer)
{
	in >> (User&)buyer;
	return in;
}
void Buyer::show() const
{ // prints buyers data
	cout << *this;
}