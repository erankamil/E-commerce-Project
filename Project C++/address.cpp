#pragma warning(disable: 4996)
#include "address.h"

#include <string>


Address::Address(const string&  country, const string&  city, const string& street, int apartmentNumber)
{
	setCity(city);
	setCountry(country);
	setStreet(street);
	setApartment(apartmentNumber);
}
Address::Address(ifstream& in)
{
	in >> *this;
}
Address::Address(const Address& other)
{
	*this = other;
}
const Address& Address::operator=(const Address& other)
{
	if (this != &other)
	{
		setCountry(other._country);
		setCity(other._city);
		setStreet(other._street);
		setApartment(other._apartmentNumber);
	}
	return *this;
}

bool Address::setCountry(const string&  country)
{
	bool res = true;
	for (int i = 0; country[i] != '\0' && res == true; i++) // runs over the sting and check if the is ivalid letter
	{
		if ((country[i] != ' ') && (country[i]<'a' || country[i] > 'z') && (country[i]<'A' || country[i] > 'Z'))
			res = false;
	}
	if (res == true) // the country name is valid
	{
		_country = country;
	}
	return res;
}
bool Address::setCity(const string& city)
{
	bool res = true;
	for (int i = 0; city[i] != '\0' && res == true; i++) // runs over the sting and check if the is ivalid letter
	{
		if (city[i] != ' ' && (city[i]<'a' && city[i] > 'z') && (city[i]<'A' && city[i] > 'Z'))
			res = false;
	}
	if (res == true) // the city name is valid
	{
		_city = city;
	}
	return res;
}
bool Address::setStreet(const string&  street)
{
	bool res = true;
	for (int i = 0; street[i] != '\0' && res == true; i++) // runs over the sting and check if the is ivalid letter
	{
		if (street[i] != ' ' && (street[i]<'a' && street[i] > 'z') && (street[i]<'A' && street[i] > 'Z'))
			res = false;
	}
	if (res == true) // the street name is valid
	{
		_street = street;
	}
	return res;
}
bool Address::setApartment(int apartmentNumber)
{
	if (apartmentNumber < 0)
		return false;
	else // valid home number
	{
		_apartmentNumber = apartmentNumber;
		return true;
	}
}
ostream& operator<<(ostream& out, const Address& a)
{ // overloading operator << 
	if (typeid(out) == typeid(ofstream)) // in case that os if ofstream - write to file
	{
		out<< a._country << " " << a._city << " " << a._street << " " << a._apartmentNumber;
	}
	else
		out <<  " Address:" << a._country << " " << a._city << " " << a._street << " " << a._apartmentNumber;
	return out;
}
istream& operator>>(istream& in, Address& address)
{
	in  >> address._country >>address._city>> address._street>> address._apartmentNumber;
	return in;
}
