#include <iostream>
#include <string>
using namespace std;

struct free_throws
{
    string name;
    int made;
    int attempts;
    float percent;
};
const free_throws & clone2(free_throws & );
void display(const free_throws & ft);
void set_pc(free_throws & ft);
free_throws & accumulate(free_throws & target, const free_throws & source);



int main(int argc, char const *argv[])
{
// partial initializations – remaining members set to 0
    free_throws one = {"Ifelsa Branch", 13, 14};
    free_throws two = {"Andor Knott", 10, 16};
    free_throws three = {"Minnie Max", 7, 9};
    free_throws four = {"Whily Looper", 5, 9};
    free_throws five = {"Long Long", 6, 14};
    free_throws team = {"Throwgoods", 0, 0};
// no initialization
    free_throws dup;

	clone2(one);
    const free_throws & aa = clone2(one);
}

const free_throws & clone2(free_throws & ft)
{
    free_throws newguy; // first step to big error
    newguy = ft;        // copy info
    cout << "ft: " << &ft << endl;
     cout << "newguy:" << &newguy << endl;
    return newguy;      // return reference to copy
}

