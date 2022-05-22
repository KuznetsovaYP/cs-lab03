#include "input.h"
#include "histogram.h"
#include "svg.h"
#include <iostream>
#include<vector>
#include <curl/curl.h>

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





int main(int argc, char* argv[])
{
    if (argc>1)
    {
        cout<<"argv[0]= "<<argv[0];
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
//Ввод данных
Input data;

        const auto input=read_input(cin,true);
//Расчет гистограммы



        const auto bins = make_histogram(input);


//Вывод данных

        size_t bin_height;
        show_histogram_svg(bins,bin_height);




    return 0;
}
