#include<iostream>
using namespace std;
#include <cstdlib> 
#include <iomanip>
int main(int argc, char const *argv[])
{
	double a = 20.40;
	cout.precision(2);
	cout << "a :" << a << endl;
	cout.precision(6);
	cout << "a(6) :" << a << endl;
  cout << fixed << right;
	cout << setprecision(6);
	cout << "a(6-2) :" << a << endl;

	return 0;
}