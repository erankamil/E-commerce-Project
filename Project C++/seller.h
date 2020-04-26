#ifndef __SELLER_H
#define  __SELLER_H

#include "address.h"
#include "product.h"
#include "feedback.h"


class Seller:virtual public User
{
protected:
	vector<Product*> _productsArr;
	Array<Feedback*> _feedbacksArr;
public:
	Seller() = default;
	Seller(const string& username, const string& password, const Address& address);
	Seller(ifstream& in);
	Seller(const Seller& other);
	~Seller();

	//get functions
	Array<Feedback*> getFeedbacks() const { return _feedbacksArr; }
	vector<Product*> getProducts() const { return _productsArr; }

	//other functions
	void AddFeedback(Feedback& feedback);
	void AddProduct(Product& product);
	void show() const;

	//operators
	const Seller& operator=(const Seller& other);

};
#endif // !__SELLER_H