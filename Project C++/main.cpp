#include "manager.h"
#include <iostream>
using namespace std;


void main()
{
	Manager* m = new Manager;;
	m->run();
	delete m;
	system("pause");
}
