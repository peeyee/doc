#include<iostream>
#include"MyComplex.cpp"

int main(int argc, char const *argv[])
{
	using namespace std;
	MyComplex a = MyComplex(1,3);
	MyComplex b = MyComplex(2,-3);
	cout << "a is " << a << endl;
	cout << "b is " << b << endl;
	cout << "a+b: " << a + b << endl;
	cout << "a*b: " << a * b << endl;
	cout << "a-b: " << a - b << endl;
	return 0;
}