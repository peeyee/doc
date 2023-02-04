#include <iostream>
#include <memory>

int main(void){
	using namespace std;
	string a = "a string in stack";
	unique_ptr<string> ps(&a);
	cout << "Bye." << endl;
}