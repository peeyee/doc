#ifndef _MYCOMPLEX_H
#define _MYCOMPLEX_H
#include<iostream>
class MyComplex 
{
	private:
	    float real;
	    float image;
	public:
		MyComplex()
		{
			real = 0.0f;
			image = 0.0f;
		};
		MyComplex(float r, float i)
		{
			real = r;
			image = i;
		};
		~MyComplex(){};
	    friend std::ostream & operator<<(std::ostream & out,const MyComplex & c);
	    MyComplex operator*(MyComplex c);
		MyComplex operator-(MyComplex c);
		MyComplex operator+(MyComplex c);
};
#endif
