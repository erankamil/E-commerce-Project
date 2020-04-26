#ifndef __PRODUCT_H
#define __PRODUCT_H
using namespace std;
#include <iostream>

class Seller;

class Product 
{
public:
	enum eCatagory { Kids, Electronics, Office_Supplies, Fashion };
	const char* CatagoryArr[4] = { "Kids" ,"Electronics" , "Office Supplies", "Fashion" };

private:
	string _name;
	int _price;
	eCatagory e_catagory;
	static int _counter;
	int _serial_number;
	Seller& _seller;

public:
	Product(const string& name, int price, int catagory,  Seller& seller);
	Product(const Product& p); //copy c'tor

	//set functions
	void setName(const string& name);
	bool setPrice(int price);
	bool setCatagory(int catagory);

	//get functions
	Seller& getSeller() const { return _seller; }
	inline const string& getName() const { return _name; }
	inline int getPrice() const { return _price; }
	int getCatagory() const { return e_catagory; }
	inline int getSerialNumber()  const { return _serial_number; }

	//operators
	friend ostream&  operator<<(ostream& os, const Product& p);

};


#endif //__PRODUCT_H