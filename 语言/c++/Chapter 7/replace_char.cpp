#include <iostream>
#include <string>
using namespace std;

int replace(char * str, char a, char b);

int main()
{
  char a[13]="huangweifeng";
   cout << "replace " << a <<" with ";
  int number = replace(a,'a','b');
  cout << number << " times." << endl;
  return 0;
}

int replace(char * str, char a, char b){
	int replace_count = 0;
	for(char * i = str; *i != '\0'; i++)
	{
		if ( *i == a)
		{
			*i = b;
			replace_count++;
		}
	}
    return replace_count;
}