#ifndef __MANAGER_H
#define __MANAGER_H
#include "buyer.h"
#include "seller.h"
#include "user.h"

class Manager 
{
private:
	vector<User*> _usersArr;
	int _num_of_sellers = 0;
	int _num_of_buyers = 0;
	int _num_of_buyersNsellers = 0;
	Manager(Manager& other);
public:

	Manager();
	~Manager();


	//manu functions
	void run();
	void doAction(int selection);
	void readUser(int selection);
	void addUserToArr(User* user_to_add);
	void addProductToSeller(int seller_index);
	int checkIfUserExist(int type);
	
	Product* checkSerialNumber(int serial_number, int index_buyer, int& isExist);
	Product* checkProductInCart(int serial_number, Cart& cart);
	Product* checkPurchasedItem(int serial_number, int buyer_index);

	bool checkDate(int day, int month, int year);
	bool isUserNameExist(const string& username);
	bool checkProductInOrder(int serial_number, Cart& order);

	void case3();
	void case4();
	void case5();
	void case6();
	void case7();

	//print functions
	void printAllProductsWithName(const string& productName);
	void printBuyerArr() const;
	void printSellerArr() const;
	void printBuyerNSellerArr() const;
	//get functions
	inline int getLogSize() const { return _usersArr.size(); }
	inline int getPhySize() const { return _usersArr.capacity(); }

	//overloading operators:
	const Manager& operator+=(User& user_to_add);
	void checkOperators();
	void compareBuyersCartPrice(int index_buyer1, int  index_buyer2);

	//file read/write functions
	void loadUsers(const string& fileName);
	void saveUsers( const string& fileName);

	enum eUserType { BUYER = 1, SELLER, BUYERNSELLER = 11 };
	const char* typeUserArr[3] = { "Buyer" ,"Seller" , "buyerNseller" };
	friend void CleanBuffer();
};

#endif // !__MANAGER_H