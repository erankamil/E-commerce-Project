#pragma warning(disable: 4996)
#include "user.h"
#include <string>

User::User(const string& username, const string& password, const Address& address ):_address(address)
{ 
	SetUserName(username);
	SetPassword(password);
}
User::User(ifstream& in):_address()
{
	in >> *this;
}
User::User(const User& other):_address(other._address)
{
	*this = other; // using the opetator= function
}
User::~User()
{
}
void User::SetUserName(const string& username)
{
	this->_username = username;
}

void User::SetPassword(const string& password)
{
	this->_password = password;
}

const User& User::operator=(const User& other)
{
	if (this != &other) // to avoid option of user=user (same one)
	{
		SetUserName(other._username);
		SetPassword(other._password);
		this->_address = other._address;
	}
	return *this;
}
ostream&  operator<<(ostream& out, const User& user)
{  // overloading operator << to print username and address of the user
	if (typeid(out) == typeid(ofstream)) // in case that os if ofstream - write to file
		out << user._username << " " << user._password << " " << user._address;
	else // write to console
		cout << "User Name:" << user._username << " " << user._address << endl;
	return out;
}
istream& operator>>(istream& in, User& user)
{
	in >> user._username;
	in >> user._password;
	in>> user._address;
	return in;
}