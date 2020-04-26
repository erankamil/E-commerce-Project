#include "buyerNseller.h"

BuyerNseller::BuyerNseller(const string& username, const string& passord,const Address&a) :User(username,passord,a),Buyer(username, passord, a),Seller(username, passord, a) {};

BuyerNseller::BuyerNseller(ifstream& in) : User(in),Buyer(in),Seller(in)
{

}

void BuyerNseller::show() const
{
		cout << *this;
}