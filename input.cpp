#include<iostream>
#include<vector>
#include "input.h"

using namespace std;

vector<double>
input_numbers(size_t count, istream& in) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}
