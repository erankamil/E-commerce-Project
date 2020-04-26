using namespace std;
#include <iostream>
#include "cart.h"



Cart::Cart()
{
}
Cart::Cart(const Cart& other)
{
	*this = other; // using operator=
}
const Cart&Cart::operator=(const Cart& other)
{
	if (this != &other)
	{
		_productsArr = other._productsArr;
		_total_price = other._total_price;
	}
	return *this;
}
void Cart::addProduct(Product& product_to_add)
{
	_productsArr.push_back(&product_to_add);
	_total_price += product_to_add.getPrice(); // adds the price of the new product to the total price of the cart
}
void Cart::saveOrder(Cart& last_order)
{ // the function gets an order by ref and adds his products to the product array 
	int log_size = _productsArr.size();
	int phy_size = _productsArr.capacity();
	int last_order_log_size = last_order._productsArr.size();
	int last_order__phy_size = last_order._productsArr.size();

	if (log_size + last_order_log_size >= phy_size) // there is not enough memory in the current array
		_productsArr.reserve(log_size + last_order_log_size); // update the physical memory
	for (int i = 0; i < last_order_log_size; i++)
		_productsArr.push_back(last_order._productsArr[i]); // add the last order item to the products array
}
void Cart::reset()
{
	_productsArr.clear();
	_total_price = 0;
}
void Cart::show() const
{
	vector<Product*>::const_iterator itr = _productsArr.begin();
	vector<Product*>::const_iterator itrEnd = _productsArr.end();
	for (int i = 0; itr!=itrEnd ; i++,itr++)
		cout << i + 1 << ")" << *(*itr);
}