#include<iostream>
#include"MyComplex.h"
using std::ostream;
MyComplex MyComplex::operator*(MyComplex a)
{
	MyComplex tmp;
	tmp.real = this->real * a.real - this->image * a.image;
	tmp.image = this->real * a.image + this->image * a.real;
	return tmp;
}

MyComplex MyComplex::operator-(MyComplex a)
{
	MyComplex tmp;
	tmp.real = this->real - a.real;
	tmp.image = this->image - a.image;
	return tmp;
}

MyComplex MyComplex::operator+(MyComplex a)
{
	MyComplex tmp;
	tmp.real = this->real + a.real;
	tmp.image = this->image + a.image;
	return tmp;
}

ostream & operator<<(ostream & out,const MyComplex & a)
{
	if(a.image < 0)
	{
		out<< a.real << a.image << "i";
		return out;
	}
	else if(a.image == 0)
	{
		out<< a.real ;
		return out;
	}
	else
	{
		out<< a.real << "+" << a.image << "i";
		return out;
	}
	return out;
}