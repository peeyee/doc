#include <iostream>
#include <string>
using namespace std;

void f(char *,int i=1);

int main(int argc, char const *argv[])
{
    char a[6] = "hello"; 
    int num;
    cout << "input n: " << endl;
    cin >> num;
    f(a,num);
	return 0;
}

void f(char * a,int i)
{
	cout << "i=" << i << ",调用：" << a << endl; 
	i--;  	
	if(i>0){f(a,i);}
	return;
}