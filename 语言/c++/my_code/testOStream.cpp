#include<iostream>

int main(int argc, char const *argv[])
{
	using std::cout;
	using std::endl;
	int eggs = 12;
	char * amout = "dozen";
	/*cout << &eggs << endl;
	cout << amout << endl;
	cout << (void *) amout;
	cout << 'W';
	*/
	long val = 560031841;
	cout << &val << endl;
	cout.write( (char *) &val, sizeof(long));
	cout <<endl;
	return 0;
}