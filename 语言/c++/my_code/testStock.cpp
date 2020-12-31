#include<iostream>
#include"Stock.cpp"
#include<string>

int main(int argc, char const *argv[])
{
	using namespace std;
	Stock stock1 = Stock("pipa",100);
	Stock stock2 = stock1;
	cout << "&stock1: " << &stock1 << endl;
	cout << "&stock2: " << &stock2 << endl;
	/* code */
	return 0;
}