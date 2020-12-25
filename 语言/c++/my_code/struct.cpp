#include <iostream>
#include <string>
using namespace std;

struct box
{
      char maker[40];
      float height;
      float width;
      float length;
      float volume;
};

void func(box);
void func2(box *);


int main(int argc, char const *argv[])
{
	box a;
	for(int i=0; i < 5; i++)
	{
		a.maker[i] = 'a';
	}
	a.height = 1.0f;
	a.width = 1.1f;
	a.length = 1.2f;
	a.volume = 1.3f;
//证明func是按值传递的
	func(a);
	// cout << "height:" << a.height << endl;
	func2(&a);
}


void func(box a)
{
	a.height = 2.0f;
	cout << "maker:" << a.maker << endl;
	cout << "height:" << a.height << endl;
	cout << "width:" << a.width << endl;
	cout << "length:" << a.length << endl;
	cout << "volume:" << a.volume << endl;
}

void func2(box * ptr)
{
	ptr->volume = ptr->height * ptr->width * ptr->length;
	cout << "maker:" << ptr->maker << endl;
	cout << "height:" << ptr->height << endl;
	cout << "width:" << ptr->width << endl;
	cout << "length:" << ptr->length << endl;
	cout << "volume:" << ptr->volume << endl;
}