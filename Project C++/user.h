
#ifndef __USER_H_
#define __USER_H_

#include "cart.h"
#include "address.h"
#include <fstream>

class User
{ // abstract calss
protected:
	 string _username;
	string _password;
	Address _address;
	User(const string& username, const string& password, const Address& address);
	User(ifstream& in);
	User(const User& other);
	virtual const User& operator=(const User& other);
public:
	
	virtual ~User();
	//set functions
	void SetPassword(const string& password);
	void SetUserName(const string& username);
	
	//get functions
	inline const string& getUserName() const { return _username; }
	inline const string& getPassword() const { return _password; }

	Address& getAddress() { return _address; }
	const Address& getAddress() const { return _address; }

	virtual void show() const=0;
	friend ostream&  operator<<(ostream& out, const User& user);
	friend istream& operator>>(istream& in, User& user);



};
#endif // !__USER_H_


