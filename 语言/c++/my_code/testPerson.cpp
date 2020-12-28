#include<iostream>
#include"Person.h"
#include"Person.cpp"

int main(int argc, char const *argv[])
{
	using namespace std;
	Person one;                      // use default constructor
	Person two("Smythecraft");       // use #2 with one default argument
	Person three("Dimwiddy", "Sam"); // use #2, no defaults
	two.Show();
	cout << endl;
	two.FormalShow();
	three.Show();
	cout << endl;
	three.FormalShow();
	return 0;
}