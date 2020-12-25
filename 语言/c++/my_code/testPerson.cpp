#include<iostream>
#include"Person.h"
#include"Person.cpp"

int main(int argc, char const *argv[])
{
	using namespace std;
	Person one;                      // use default constructor
	Person two("Smythecraft");       // use #2 with one default argument
	Person three("Dimwiddy", "Sam"); // use #2, no defaults
	one.Show();
	cout << endl;
	one.FormalShow();

	return 0;
}