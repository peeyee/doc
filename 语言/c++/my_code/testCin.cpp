// cinexcp.cpp -- having cin throw an exception
#include <iostream>
#include <exception>

int main()
{
    using namespace std;
    // have failbit cause an exception to be thrown
    cin.exceptions(ios_base::failbit);
    cout << "Enter numbers: ";
    int sum = 0;
    int input;
    try {
        while (cin >> input)
        {
            sum += input;
        }
    } catch(ios_base::failure & bf)
    {
        cout << bf.what() << endl;
        cout << "O! the horror!\n";
    }

    cout << "Last value entered = " << input << endl;
    cout << "Sum = " << sum << endl;
/* keeping output window open */

	cin.clear();
	printf("%s\n", cin.get());
	// while (!isspace(cin.get()))
	//     continue; // get rid of bad input
	// cout << "Now enter a new number: ";
	// cin >> input; // won't work


    return 0;
}


