#pragma warning(disable: 4996)
#include "product.h"
#include <string>

Product::Product(const string& name, int price, int catagory,  Seller& seller) :_serial_number(++_counter),_seller(seller)
{
	setName(name);
	setPrice(price);
	setCatagory(catagory);
}
Product::Product(const Product& p):_serial_number(++_counter), _seller(p._seller)
{
	setName(p._name);
	setPrice(p._price);
	setCatagory(p.e_catagory);
}
void Product::setName(const string& name) //product name can include different kinds of characters
{
	this->_name = name;
}
bool Product::setPrice(int price)
{
	if (price <= 0)  // price need to be positive number
		return false;
	_price = price;
	return true;
}
bool Product::setCatagory(int catagory)
{
	if (catagory > 3 || catagory < 0) // there is only 4 catagories
		return false;
	e_catagory = (eCatagory)catagory;
	return true;
}
ostream& operator<<(ostream& os, const Product& p)
{ // overloading operator << 
	os << p._name << " " << "price:" << p._price << " catagory:" << p.CatagoryArr[p.e_catagory] << " S/N:" << p._serial_number<<endl;
	return os;
}
 int Product::_counter = 999;