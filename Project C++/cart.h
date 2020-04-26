#ifndef __CART_H
#define __CART_H
#include "product.h"
#include "array.h"
#include <vector>

class Cart
{
private:
	vector<Product*> _productsArr;
	int _total_price = 0;
public:
	Cart();
	Cart(const Cart& c);

	//get functions 
	inline  vector<Product*> getProductsArr() const { return _productsArr; }
	inline int getTotalPrice()const { return _total_price; }

	//other functions
	void addProduct(Product& product_to_add);
	void saveOrder(Cart& last_order);
	void reset();
	void show()const;
	const char* CatagoryArr[4] = { "Kids" ,"Electronics" , "Office Supplies", "Fashion" };

	// operators
	const Cart& operator=(const Cart& other);

};

#endif // !__CART_H


