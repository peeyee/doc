#include <iostream>
using namespace std;

void swap(int & a, int & b);

int main(int argc , char * argv[]){
    int a = 3;
    int b = 4;
    cout << "a new line !" << endl;
    cout << "before swap a:" << a << ",b:" << b << endl;
    swap(a, b);
    cout << "after swap a:" << a << ",b:" << b << endl;
    swap(b,a);
    swap(b,a);
}


void swap(int & a, int & b){
    int temp = b;
    b = a;
    a = temp;
}