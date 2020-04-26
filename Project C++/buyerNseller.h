#ifndef __BUYERNSELLER_H
#define __BUYERNSELLER_H

#include "buyer.h"
#include "seller.h"

class BuyerNseller :public Buyer, public Seller
{
public:
	BuyerNseller(const string&  username, const string& passord, const Address&a);
	BuyerNseller(ifstream& in);
	void show() const;
};


#endif // !__BUYERNSELLER_H
