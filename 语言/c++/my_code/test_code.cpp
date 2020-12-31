#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	const char * const months[12] =
	{
	    "January", "February", "March", "April", "May",
	    "June", "July", "August", "September", "October",
	    "November", "December"
	};
	cout << *months;
	return 0;
}
