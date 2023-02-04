#include<iostream>
#include <bitset>

int main(int argc, char const *argv[])
{
	using namespace std;
	double d = 20.40;
	double e = 20.30;
	//cout << "d + e is" << (d + e) << endl;
	//cout << (bit) d << endl;
	cout << bitset<sizeof(double) * 8>(d) << endl;
	cout << d;
	return 0;
}

01100110011001100110011001100110011001100110011

10100.01100110 01100110 01100110 01100110 01100110 0110011
64 1 