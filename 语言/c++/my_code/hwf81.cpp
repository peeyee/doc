#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	string input;
	cout << "Enter a string (q to quit): ";
    getline(cin,input);
    if(input == "q")
    {
    	 cout << "Bye." << endl;
    	 return 0;
    }
    cout << input << endl;
    cout << "Next string (q to quit): ";
    string a;
    getline(cin,a);
    while(a!="q")
    {
        cout << a << endl;
        cout << "Next string (q to quit): ";
        getline(cin,a);
    }
    cout << "Bye." << endl;

return 0;
}

