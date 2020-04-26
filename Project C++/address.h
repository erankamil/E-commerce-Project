#ifndef __ADRESS_H
#define __ADRESS_H
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Address
{
private:
	string _country;
	string _city;
	string _street;
	int  _apartmentNumber;

public:
	//c'tor
	Address(const string& country, const string& city, const string& street, int apartmentNumber);
	Address() = default; // we use default ctor for reading from file 
	Address(ifstream& in);
	Address(const Address& a); //copy c'tor
	
	//set functions
	bool setCountry(const string&  country);
	bool setCity(const string&  city);
	bool setStreet(const string&  street);
	bool setApartment(int number);

	//gets functions
	inline const string&  getCountry() const { return _country; }
	inline const string&  getCity() const { return _city; }
	inline const string&  getStreet() const { return _street; }
	inline const int&  getApartmentNumber() const { return _apartmentNumber; }

	//operators
	friend ostream& operator<<(ostream& out, const Address& a);
	const Address& operator=(const Address& other);
	friend istream& operator>>(istream& in, Address& address);

};



#endif //__ADRESS_H