#ifndef __BUYER_H
#define __BUYER_H
#include "address.h"
#include "product.h"
#include "cart.h"
#include "user.h"

class Buyer: virtual public User
{
protected:
	Cart _purchaseHistory;
	Cart _order;
	Cart _cart;
public:
	//c'tor
	Buyer() = default;
	Buyer(const string& username, const string& password, const Address& address);
	Buyer(ifstream& in);
	//d'tor
	Buyer (const Buyer& other);

	Cart& getPurchaseHistory() { return _purchaseHistory; }
	const Cart& getPurchaseHistory() const { return _purchaseHistory; }
	Cart& getOrder() { return _order; }
	const Cart& getOrder() const { return _order; }
	Cart& getCart() { return _cart; }
	const Cart& getCart() const { return _cart; }

	//other functions
	void saveOrder();
	void addProudctToOrder( Product& product_to_add);
	void addToCart(Product& product_to_add);
	void show() const;
	
	//operators
	const string& operator>(const Buyer& user2);
	const Buyer& operator=(const Buyer& other);
	friend istream& operator>>(istream& in, const Buyer& buyer);
};


#endif // !__BUYER_H
