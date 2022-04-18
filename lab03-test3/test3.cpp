#include "../input.h"
#include<cassert>
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

void
test_1()
{
    int n=5;
    string stream="1 2 4 7 3";
    istringstream str(stream);
    vector<double>in=input_numbers(n,str);
    assert(in[0]==1);
    assert(in[1]==2);

}

int main()
{
    test_1();
}
