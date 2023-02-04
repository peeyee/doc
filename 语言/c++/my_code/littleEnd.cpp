#include<iostream>
using namespace std;
int main()
{
	short big = 0xff00;
	char litter = big;
	if (litter == 0xff)
	{
		cout << "大端" << endl;
	}
	else
	{
		cout << "小端" << endl;
	}
    return 0;
}
