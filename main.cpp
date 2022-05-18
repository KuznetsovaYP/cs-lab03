#include "input.h"
#include "histogram.h"
#include "svg.h"
#include <iostream>
#include<vector>

using namespace std;


Input
read_input(istream& in, bool prompt) {
    Input data;
    size_t number_count;
    if (prompt)
    {

    cerr<<"Enter number count: ";
    in>>number_count;

    cerr<<"Enter numbers: ";
    data.numbers=input_numbers(number_count,in);

        cerr<<"Enter bin count: ";
        in>>data.bin_count;
    }
    else
    {
        in>>number_count;
        data.numbers=input_numbers(number_count,in);
        in>>data.bin_count;
    }

    return data;
}





int main()
{
//���� ������
Input data;

        const auto input=read_input(cin,true);
//������ �����������



        const auto bins = make_histogram(input);


//����� ������

        size_t bin_height;
        show_histogram_svg(bins,bin_height);




    return 0;
}
