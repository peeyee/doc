#include<iostream>
#include"Person.h"
#include <cstring>

void Person::Show() const
{
  using namespace std;
  cout << fname << " " << lname << endl;
}


void Person::FormalShow() const
{
  using namespace std;
  cout << lname << ", " << fname << endl;
}

Person(const string & ln, const char * fn = "Heyyou")
{
  lname=ln;
  strcpy(fname,fn);
}