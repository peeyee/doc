#include <iostream>
#include <string>
using namespace std;




int main(int argc, char const *argv[])
{
int rat = 10;
int & rotent = rat;
int mouse = 20;
cout << "rotent add is " << &rotent << endl;
cout << "rotent value is " << rotent << endl;
rotent = mouse;
cout << "ater rotent = mouse:" << endl;
cout << "rotent add is " << &rotent << endl;
cout << "rotent value is " << rotent << endl;
cout << "&mouse =" << &mouse << endl;
// rotent = &mouse;
cout << "ater rotent = &mouse" << endl;
cout << "rotent value is " << rotent << endl;

return 0;

}

