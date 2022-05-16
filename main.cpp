#include "input.h"
#include "histogram.h"
#include "svg.h"
#include <iostream>
#include<vector>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
};


Input
read_input(istream& in) {
    Input data;

    cerr<<"Enter number count: ";
    in>>data.number_count;

    cerr<<"Enter numbers: ";
    data.numbers=input_numbers(data.number_count,in);

        cerr<<"Enter bin count: ";
        in>>data.bin_count;

    return data;
}

vector<size_t>
make_histogram(const vector<double> &numbers,size_t &bin_count, size_t number_count,double bin_size, double& min) {
    vector<size_t> bins(bin_count);
    for (size_t i = 0; i < number_count; i++)
        {
            bool found = false;
            for (size_t j = 0; j < (bin_count-1) && !found; j++)
            {
                auto lo = min + bin_size * j;
                auto hi = min + bin_size * (j+1);

                if ((lo <= numbers[i]) && (numbers[i] < hi))
                {
                    bins[j]++;
                    found = true;
                }

            }
            if(!found)
            {
                bins[bin_count-1]++;
            }
        }
        return bins;
}



int main()
{
//Ввод данных
        Input data;


        read_input(cin);
//Расчет гистограммы

        double min;
        double max;

        find_minmax(data.numbers,min,max);

        double bin_size = (max-min) / data.bin_count;
        const auto bins = make_histogram(data.numbers, data.bin_count,data.number_count,bin_size,min );


//Вывод данных

        size_t bin_height;
        show_histogram_svg(bins,bin_height);




    return 0;
}
