#include "manager.h"
#include "buyer.h"
#include "seller.h"
#include "cart.h"
#include "buyerNseller.h"
#include <fstream>
#include <string>
#include <vector>

void CleanBuffer()//this function cleans the buffer for using getline function
{
	char c;
	do
	{
		c = getchar();
	} while (c != EOF && c != '\n');
}
Manager::Manager()//c'tor // set log and phyiscal size // allocate's buyers and seller array
{
}
Manager::~Manager()//d'tor // delete all buyers and sellers in the system
{
	int size = _usersArr.size();
	for (int i = 0; i < size; i++)
		delete  _usersArr[i];
}
void Manager::run()//runs the menu of the system
{
	int selection=0;//user selection
	ifstream inFile("users.txt", ios::_Nocreate);
	if (inFile.is_open()) // in case file has users already 
		loadUsers("users.txt"); // load the users to the program
	while (selection!=14)//continue until user press 11
	{
		//show menu on the screen
		cout << "-----------------------------------------------" << endl;
		cout << "Welcome to the trade system menu:" << endl;
		cout << "Press 1 to add  buyer" << endl;
		cout << "Press 2 to add a seller" << endl;
		cout << "Press 3 to add product to seller" << endl;
		cout << "Press 4 to give feedback" << endl;
		cout << "Press 5 to add product to your cart" << endl;
		cout << "Press 6 to order products from cart" << endl;
		cout << "Press 7 for payment" << endl;
		cout << "Press 8 to print all buyers data" << endl;
		cout << "Press 9 to print all Sellers data" << endl;
		cout << "Press 10 to search for a product" << endl;
		cout << "Press 11 to add a buyer&seller user" << endl;
		cout << "Press 12 to print all buyers&sellers data" << endl;
		cout << "Perss 13 to check operators " << endl;
		cout << "Press 14 to exit " << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "Your choice:";
		cin >> selection;//get user selection
		cout << endl;//action in accordance to the user select
		doAction(selection);
	}
}

void Manager::addUserToArr(User* user_to_add)
{//functions gets pointer to user and add to the array
	_usersArr.push_back(user_to_add);
}
void Manager::readUser(int selection) //this function, gets user data 
{
	int homeNumber;
	string username, password, country, city, street;
	cout << "please enter your user name: ";
	getline(cin,username);//get user name
	cout << "please enter your user password: ";
	getline(cin, password);//get password
	cout << "please enter your country: ";
	getline(cin, country);// get country
	cout << "please enter your city: ";
	getline(cin, city);//get city
	cout << "please enter your street: ";
	getline(cin, street);// get street
	cout << "please enter your home number: ";
	cin >> homeNumber;//get home number
	if (isUserNameExist(username)) // the user name is valid
	{
		Address a(country, city, street, homeNumber);//create address
		if (selection == BUYER) // create buyer
		{
			User* user_to_add = new Buyer(username, password, a);
			addUserToArr(user_to_add);//add to user's array
			_num_of_buyers++;
		}
		if (selection == SELLER) // create buyer
		{
			User* user_to_add = new Seller(username, password, a);
			addUserToArr(user_to_add);//add to user's array
			_num_of_sellers++;
		}
		if (selection == BUYERNSELLER || selection+8== BUYERNSELLER) // create buyer&seller selection 3 or 11 enum
		{
			User* user_to_add = new BuyerNseller(username, password, a);
			addUserToArr(user_to_add);//add to user's array
			_num_of_buyersNsellers++;
		}
		cout << "User:" << username << " has joined to the system!" << endl;
	}
}

bool  Manager::isUserNameExist(const string& username)
{ // checks if there is a user with the same username 
	vector<User*>::const_iterator itr = _usersArr.begin();
	vector<User*>::const_iterator itrEnd = _usersArr.end();
	for (; itr != itrEnd; itr++)
	{
		if (username==(*itr)->getUserName())
		{
			cout << "Username already exist" << endl;
			return false;
		}
	}
	return true;
}
bool  Manager::checkDate(int day,int month,int year)
{ // checks if the date is valid
	if ((day < 1 || day>31) || (month < 1 || month>12) || (year < 2000))
	{
		cout << "Invalid date" << endl;
		return false;
	}
	return true;
}
void Manager::addProductToSeller(int seller_index)
{//the function gets index of seller in the array, allocates product and add's it to the current seller products

	//gets product data
	string name;
	int price, catagory;
	cout << "Please enter the product name: ";
	getline(cin,name);
	cout << "Please enter the product price: ";
	cin >> price;
	cout << "Please Enter the product catagory(0.Kids 1.Electronics 2.Office Supplies 3.Fashion): ";
	cin >> catagory;
	Seller* temp_seller = dynamic_cast<Seller*>(_usersArr[seller_index]);
	Product* product_to_add = new Product(name, price, catagory, *temp_seller);
	//allocates new product with the given data
	temp_seller->AddProduct(*product_to_add);//add's to the seller products array
}
int Manager::checkIfUserExist(int type)
{//this function asks the user to log in, and checks log in successfully
	//gets User data
	int index_to_return = -1;
	string username, password;
	cout << "please enter your user name: ";
	getline(cin,username);
	cout << "please enter your user password: ";
	getline(cin,password);
	//checks the given data is in the array
	vector<User*>::const_iterator itr = _usersArr.begin();
	vector<User*>::const_iterator itrEnd = _usersArr.end();
	for (int i=0; itr != itrEnd; itr++,i++)
	{
		if (type == SELLER || type==BUYERNSELLER) //  user trying to log in as seller
		{
			Seller* temp_seller = dynamic_cast<Seller*>(*itr);
			if (temp_seller)
			{
				if (((*itr)->getUserName()==username) && ((*itr)->getPassword()==password))
				{
					index_to_return = i;
					cout << endl << "Log in succeeded!" << endl << endl;
				}
			}
		}
		if (type == BUYER || type == BUYERNSELLER) //  user trying to log in as  buyer 
		{
			Buyer* temp_buyer = dynamic_cast<Buyer*>(*itr);
			if (temp_buyer)
			{
				if ((*itr)->getUserName()==username && ((*itr)->getPassword()==password))
				{
					index_to_return = i;
					cout << endl << "Log in succeeded!" << endl << endl;
				}
			}
		}
	}
	return index_to_return;
}
Product* Manager::checkSerialNumber(int serial_number, int index_buyer, int&isExist)
{ //the function checks the given serial number exist
	Buyer* temp_buyer = dynamic_cast<Buyer*>(_usersArr[index_buyer]);
	vector<Product*>  products_in_cart = temp_buyer->getCart().getProductsArr();
	vector<Product*>::const_iterator itr = products_in_cart.begin();
	vector<Product*>::const_iterator itrEnd = products_in_cart.end();
	for (; itr!= itrEnd; itr++) //checks the buyer didnt add the product already
	{
		if (serial_number == (*itr)->getSerialNumber())
			isExist = true;
	}
	int size = _usersArr.size();
	if (!isExist) //in case buyer didnt had yet
	{	 //runs on the users array

		for (int i = 0; i < size; i++)
		{//get size and product array
			Seller* temp_seller = dynamic_cast<Seller*>(_usersArr[i]);
			BuyerNseller* temp_buyerseller = dynamic_cast<BuyerNseller*>(_usersArr[i]);
			if (temp_seller || temp_buyerseller) // the current user in the array is seller or buyerNseller
			{
				vector<Product*> curr_seller_products = temp_seller->getProducts();
				int size_of_products = curr_seller_products.size();
				for (int j = 0; j < size_of_products; j++)
				{

					if (serial_number == curr_seller_products[j]->getSerialNumber()) // we found the product 
						return curr_seller_products[j]; //returns the relevant product
				}
			}

		}
	}
	return nullptr; //in case serial number doesnt exist
}
 Product* Manager::checkPurchasedItem(int serial_number,int buyer_index)
 { //the function check if the buyer bought the current product by his seiral number
	 //runs on his product array
	 Buyer* temp_buyer = dynamic_cast<Buyer*>(_usersArr[buyer_index]);
	 int size = temp_buyer->getPurchaseHistory().getProductsArr().size();
	 for (int i = 0; i < size ; i++)
	 {
		 //checks if same seiral number
		 if (serial_number == temp_buyer->getPurchaseHistory().getProductsArr()[i]->getSerialNumber())
			 return  temp_buyer->getPurchaseHistory().getProductsArr()[i];
	 }
	 return nullptr;
 }
 Product* Manager::checkProductInCart(int serial_number, Cart& cart)
 {   //checks if the given serial number exist in the cart
	 vector<Product*> products_in_cart = cart.getProductsArr();
	 int size = products_in_cart.size();
	 for (int i = 0; i < size; i++)
	 {
		 if (serial_number == products_in_cart[i]->getSerialNumber())
		 {
			 return products_in_cart[i]; //if found return the relevant product
		 }
	 }
	 return nullptr; //in case didn't find
 }
 bool Manager::checkProductInOrder(int serial_number, Cart& order)
 { //checks if the given serial number exist in the order
	 bool isFound = false;
	 vector<Product*> products_in_order = order.getProductsArr();
	 int size = products_in_order.size();
	 for (int i = 0; i < size; i++) //runs on the order
	 {  //compare seiral number and checks if exist
		 if (serial_number == products_in_order[i]->getSerialNumber())
		 {
			 isFound = true;
			 return isFound;
		 }
	 }
	 return isFound;
 }
	 void Manager::doAction(int selection)
	 {
		 CleanBuffer();
		 switch (selection)
		 {
		 case 1: // add buyer to system
		 {
			 readUser(selection);
			 break;
		 }
		 case 2: // add seller to system
		 {
			 readUser(selection);
			 break;
		 }
		 case 3: // add product to seller
		 {
			 case3();
			 break;
		 }
		 case 4: // add feedback to seller
		 {
			 case4();
			 break;
		 }
		 case 5: // add product to buyer's cart
		 {
			 case5();
			 break;
		 }
		 case 6: // make order from cart
		 {
			 case6();
			 break;
		 }
		 case 7: // payment
		 {
			 case7();
			 break;
		 }
		 case 8: // print all buyers data
		 {
			 if (_num_of_buyers == 0) // there is no seller in the system
				 cout << "There is no buyers in the system yet" << endl;
			 else
				 printBuyerArr();
			 break;
		 }
		 case 9: // print all sellers data
		 {
			 if (_num_of_sellers == 0) // there is no seller in the system
				 cout << "There is no sellers in the system yet" << endl;
			 else
				 printSellerArr();
			 break;
		 }
		 case 10: // search for specific item
		 {
			 if (_num_of_sellers == 0) // there is no seller in the system
				 cout << "There is no products in the system yet" << endl;
			 else
			 {
				 string product_name;
				 cout << "Please enter the name of product you search for: ";
				 getline(cin,product_name);
				 printAllProductsWithName(product_name);
			 }
			 break;
		 }
		 case 11: // add buyer&seller type to the system
		 {
			 readUser(selection); 
			 break;
		 }
		 case 12: // print buyer&seller users data
		 {
			 if (_num_of_buyersNsellers == 0) // there is no seller in the system
				 cout << "There is no buyers&seller in the system yet" << endl;
			 else
				 printBuyerNSellerArr();
			 break;
		 }
		 case 13: // checks the operators +=,>,<<
		 {
			 checkOperators();
			 break;
		 }
		 case 14:
		 { //exit
			 saveUsers( "users.txt");
			 cout << "Bye Bye!!" << endl;
			 break;
		 }
		 default:
		 {
			 cout << "Invalid input\n";
		 }
		 }
	 }

	 void Manager::case3()
	 { // add product to sellers cart
		 if (_usersArr.size() == 0) //in case size 0, there aren't sellers in the system
		 {
			 cout << "Sorry, there is no sellers/buyers in the system.." << endl;
		 }
		 else
		 {
			 int index_seller = checkIfUserExist(SELLER);//check seller exist by log in
			 if (index_seller != -1) // the seller is exist in the system
			 {
				 addProductToSeller(index_seller);
				 cout << "The product added successfully!" << endl;
			 }
			 else // the seller was not found
				 cout << "Log in failed!" << endl;
		 }
	 }
	 void Manager::case4()
	 {  // add feedback to seller
		 if (_usersArr.size() == 0)//in case size 0, there aren't buyers in the system
			 cout << "Sorry, there is no buyers/sellers in the system.." << endl << endl;
		 else
		 {
			 int index_buyer = checkIfUserExist(BUYER); //check buyer exist by log in
			 if (index_buyer != -1) // the buyer is exist in the system
			 {
				 Buyer* temp_buyer = dynamic_cast<Buyer*>(_usersArr[index_buyer]); // cast to the current buyer
				 int purchase_history_size= temp_buyer->getPurchaseHistory().getProductsArr().size();
				 if (purchase_history_size) // the buyer bought already items
				 {
					 int serial_number;
					 cout << "Pruchase history:" << endl;
					 temp_buyer->getPurchaseHistory().show();//shows all the items the buyer bought
					 cout << "Enter the serial number of the product you want to give feedback:" << endl;
					 cin >> serial_number;
					 Product* product_to_feedback = checkPurchasedItem(serial_number, index_buyer);
					 if (product_to_feedback) // the product exist in the purchase history
					 { //get feedback data, text and date
						 CleanBuffer();
						string text;
						 cout << "Pleae enter the feedback:" << endl;
						getline(cin,text);
						 int year, month, day;
						 cout << "Enter today's date please:(eg 20 12 2019)" << endl;
						 cin >> day >> month >> year;
						 if (checkDate(day, month, year)) // checks if the date is valid
						 {
							 Date date(day, month, day); //create new feedback
							 Feedback* buyer_feedback = new Feedback(temp_buyer->getUserName(), text, date); //adds the feedback to the seller 
							 product_to_feedback->getSeller().AddFeedback(*buyer_feedback);
							 cout << "The feedback added successfully!" << endl;
						 }
					 }
					 else
						 cout << "Product does not exist in your pruchased history" << endl;
				 }
				 else
					 cout << "You did not purchase any items yet" << endl;
			 }
			 else
				 cout << "Log in failed!" << endl;
		 }
	 }
	 
void Manager::case5() 
{ // add product to buyers cart
	if (_usersArr.size() == 0) //in case size is zero, there aren't buyers yet
		cout << "Sorry, there is no sellers/buyers in the system.." << endl;
	else
	{
		int index_buyer = checkIfUserExist(BUYER);
		if (index_buyer != -1) // the buyer is exist in the system
		{
			int serial_number, isExist = false;
			cout << "Please enter the serial number of the product: ";
			cin >> serial_number; //get serial number from the user
			//check serial number exist and that product added only once
			Product* product_to_add = checkSerialNumber(serial_number, index_buyer, isExist);
			if (isExist)
				cout << "Product already exist" << endl;
			else
			{
				if (product_to_add) // the product exist in the system
				{
					Buyer* temp_buyer = dynamic_cast<Buyer*>(_usersArr[index_buyer]);
					temp_buyer->addToCart(*product_to_add); //adds relevant product to the cart
					cout << "The product:" << product_to_add->getName() << " added successfully!" << endl << endl;
				}
				else
					cout << "Product did not found in the system.." << endl << endl;
			}
		}
		else
			cout << "Log in failed!" << endl;
	}
}
 void Manager::case6()
 { // add products from buyers cart to order 
	 if (_usersArr.size() == 0) //checks first there are users in the system
		 cout << "Sorry, there is no buyers/sellers in the system.." << endl << endl;
	 int serial_number;
	 int index_buyer = checkIfUserExist(BUYER); //checks the given index relavent 
	 if (index_buyer != -1) //buyer exist
	 {
		 Buyer* temp_buyer = dynamic_cast<Buyer*>(_usersArr[index_buyer]);
		 if (temp_buyer->getCart().getProductsArr().size() == 0) //in case cart is empty
			 cout << "Your cart is empty" << endl;
		 else
		 { //cart isnt empty
			 cout << "Your cart:" << endl;
			 temp_buyer->getCart().show(); //print currernt buyer cart
			 bool flag = true;
			 while (flag) //continue until the user chose to stop
			 {
				 cout << "please enter serial number of the product you want to add:";
				 cin >> serial_number;
				 Product* product_to_add = checkProductInCart(serial_number, temp_buyer->getCart());
				 //checks the product exist in the current cart
				 if (product_to_add)
				 { //in case product is exist, add it to the order
					 if (!checkProductInOrder(serial_number, temp_buyer->getOrder()))
					 { //adds the product from the buyer cart to order
						 temp_buyer->addProudctToOrder(*product_to_add);
						 cout << "product:"<< product_to_add->getName()<<" added successfully!" << endl;
					 }
					 else
						 cout << "product already ordered" << endl;
				 }
				 else
					 cout << "Product did not found in your cart.." << endl;
				 cout << "Press 1 to add more items to order" << endl;
				 cout << "Press 0 To end your order" << endl;
				 cout << "Your choice:";
				 cin >> flag;
				 if (flag != 0 && flag != 1)
				 {
					 cout << "invalid input";
					 break;
				 }
			 }
		 }
	 }
	 else
		 cout << "Log in failed!" << endl;
 }
 void Manager::case7()
 { // payment for the buyers order
	 if (_usersArr.size() == 0) //check buyer exist by log in
		 cout << "Sorry, there is no buyer in the system.." << endl << endl;
	 int index_buyer = checkIfUserExist(BUYER);
	 if (index_buyer != -1) //buyer exist
	 {
		 Buyer* temp_buyer = dynamic_cast<Buyer*>(_usersArr[index_buyer]);
		 {
			 if (temp_buyer->getOrder().getProductsArr().size()== 0)//ther is nothing in buyers order
				 cout << "There is no items in your order.." << endl;
			 else // there is items in the buyers order
			 {
				 cout << "Total price for your order:" << temp_buyer->getOrder().getTotalPrice()<<"$";
				 cout << " paid successfully, your order on the way!" << endl << endl;
				 temp_buyer->saveOrder(); //save all the item that order to purchase history

			 }
		 }
	 }
 }
 void Manager::printAllProductsWithName(const string& productName)
 {  //prints all the products with the same name

	 bool isExist = false;
	 int size = _usersArr.size();
	 for (int i = 0; i < size; i++)
	 {	 	//runs on the users array
		 Seller* temp_seller = dynamic_cast<Seller*>(_usersArr[i]);
		 BuyerNseller* temp_buyerseller = dynamic_cast<BuyerNseller*>(_usersArr[i]);
		 if (temp_seller || temp_buyerseller) // the current user in the array is seller or buyerNseller
		 {
			 vector<Product*> curr_seller_products = temp_seller->getProducts();
			 int size = temp_seller->getProducts().size();
			 for (int j = 0; j < size; j++)
			 {	//checks each seller products

				 if (productName.compare(curr_seller_products[j]->getName()) == 0) // search for products with the same name
				 {
					 cout << *curr_seller_products[j];//if found, print
					 isExist = true;
				 }
			 }
		 }
	 }
	 if (!isExist) // we didnt find products with the name
		 cout << productName << " does not exist in the system" << endl;
 }
 void Manager::printBuyerArr() const
 { // prints the  buyers in the system
	 cout << "Buyers:" << endl;
	 vector<User*>::const_iterator itr = _usersArr.begin();
	 vector<User*>::const_iterator itrEnd = _usersArr.end();
	 for (; itr != itrEnd; itr++)
	 {
		Buyer* temp_buyer = dynamic_cast<Buyer*>(*itr);
		BuyerNseller*  temp_buyer_seller = dynamic_cast<BuyerNseller*>(*itr);
		 if (temp_buyer && (!temp_buyer_seller))// print just the users type:Buyer
			 temp_buyer->show();
	 }
 }
 void Manager::printSellerArr() const
 {// prints the  seller in the system
	 cout << "Sellers:" << endl;
	 vector<User*>::const_iterator itr = _usersArr.begin();
	 vector<User*>::const_iterator itrEnd = _usersArr.end();
	 for (; itr != itrEnd; itr++)
	 {
		 Seller* temp_seller = dynamic_cast<Seller*>(*itr);
		 BuyerNseller*  temp_buyer_seller = dynamic_cast<BuyerNseller*>(*itr);
		 if (temp_seller && (!temp_buyer_seller)) // print just the users type:Seller
		 {
			 temp_seller->show();
		 }
	 }
 }
 void Manager::printBuyerNSellerArr() const
 {// prints the  buyers&seller in the system
	 cout << "Buyers&Sellers:" << endl;
	 vector<User*>::const_iterator itr = _usersArr.begin();
	 vector<User*>::const_iterator itrEnd = _usersArr.end();
	 for (; itr!=itrEnd; itr++)
	 {
		 BuyerNseller* temp_buyer_seller = dynamic_cast<BuyerNseller*>(*itr);
		 if (temp_buyer_seller) // print just the users type:BuyerNseller
			 temp_buyer_seller->show();
	 }
 }
 void Manager::checkOperators()
 {  // the function checks the operators +=,>,>> according to the user input choise
	 int type;
	 cout << "Choose the operator you want to check:" << endl;
	 cout << "Press 1 for += operator" << endl;
	 cout << "Press 2 for > operator" << endl;
	 cout << "Press 3 for << operator" << endl;
	 cout << "Your choise:";
	 cin >> type;
	 switch (type)
	 {
	 case 1:
	 { //operator +=
		 int user_type;
		 cout << "Choose type of user to add: 1)Buyer 2)seller 3)buyer&seller" << endl;
		 cin >> user_type;
		 if (user_type != BUYER && user_type != SELLER && user_type+8 != BUYERNSELLER)
		 {
			 cout << "Invalid option" << endl;
			 break;
		 }
		 else
		 {
			 CleanBuffer();
			 readUser(user_type); // the functuion uses the operator += to add user to the users array
			 cout << endl;
			 //prints the relevant type to show added successfully
			 if (user_type == BUYER)
				 printBuyerArr();
			 else if (user_type == SELLER)
				 printSellerArr();
			 else // buyer&seller typr of user
				 printBuyerNSellerArr();
		 }
		 break;
	 }
	 case 2:
	 { //compare two buyers cart total cost
		 if (_num_of_buyers < 2)
		 {
			 cout << "There are not two different buyers to compare" << endl;
			 break;
		 }
		 printBuyerArr();
		 printBuyerNSellerArr();
		 CleanBuffer();
		 cout << "Please enter the names of the buyers you want to compare:" << endl;
		 //checks the names are exist
		 int index_buyer1 = checkIfUserExist(BUYER);
		 int index_buyer2 = checkIfUserExist(BUYER);
		 if (index_buyer1 == -1 || index_buyer2 == -1)
		 {
			 cout << "Invalid input" << endl;
			 break;
		 }
		 //compare the relevant carts total cost by using operator ">"
		 compareBuyersCartPrice(index_buyer1, index_buyer2);
		 break;
	 }
	 case 3:
	 { //tests "<<" operator
		 if (_usersArr.size() > 0)// example of using operator <<  in address of user 
			 _usersArr[0]->show();
		 else
			 cout << "You need to add user for checking operator >> " << endl;
		 break;
	 }
	 default:
	 {
		 cout << "Invalid input" << endl;
		 break;
	 }
	 }
 }
 void Manager::compareBuyersCartPrice(int index_buyer1, int  index_buyer2)
 { // the function gets 2 buyers and uses operator > to compare the total price of their carts
	 Buyer* buyer1 = dynamic_cast<Buyer*>(_usersArr[index_buyer1]);
	 Buyer* buyer2 = dynamic_cast<Buyer*>(_usersArr[index_buyer2]);
	 cout << "The buyer:" << (*buyer1 > *buyer2) << " has more expensive cart" << endl;
 }
 void Manager::saveUsers(const string& fileName)
 { // the function write the users array to the file
	 ofstream outFile(fileName,ios::trunc); // open the file for writing
	 int size = _usersArr.size();
	 outFile << size <<endl;
	 for (int i = 0; i < size; i++) // each user write his typeid
	 {
		 outFile << typeid(*_usersArr[i]).name() + 6 <<" "<< *_usersArr[i] << endl;
	 }
	 outFile.close();

 }
void Manager::loadUsers(const string& fileName)
 {
	 ifstream inFile(fileName, ios::in);
	 int size;
	 inFile >> size;
	 _usersArr.reserve(size);
	 for (int i = 0; i < size; i++)
	 {
		 string type;
		 inFile >> type; // read the type of user
		 if (type==typeUserArr[0]) // type:Buyer
		 {
			 User* new_user= new Buyer(inFile);
			 _usersArr.push_back(new_user);
			 _num_of_buyers++;
		 }
		 else if (type==typeUserArr[1]) // type:Seller
		 {
			 User* new_user = new Seller(inFile);
			 _usersArr.push_back(new_user);
			 _num_of_sellers++;
		 }
		 else// type:buyerNseller
		 {
			 User* new_user = new BuyerNseller(inFile);
			 _usersArr.push_back(new_user);
			 _num_of_buyersNsellers++;
		 }
	 }
	 inFile.close();
 }