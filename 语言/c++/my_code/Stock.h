#ifndef _STOCK_H
#define _STOCK_H
#include<string>
using std::string;
class Stock
{
public:
	Stock()
	{
		name="default"; price=0.0f;
	};
	Stock(string n,float p)
	{
		name = n; price = p;
	};
	~Stock(){};
	string getName();
	float getPrice();
private:
	string name;
	float price;	
};

#endif