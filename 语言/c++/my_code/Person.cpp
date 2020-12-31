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

Person::Person(const string & sln, const char * cfn)
{
  lname=sln;
  strcpy(fname,cfn);
}