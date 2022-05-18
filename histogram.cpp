#include "histogram.h"

using namespace std;

void
find_minmax(const vector<double> &numbers, double &min, double &max) {
    if (numbers.size()==0)
    {
        return;
    }
    else
    {
        for(double number:numbers)
            {
                if (min>number)
                {
                    min=number;
                }
                else if(max<number)
                {
                    max=number;
                }
            }
        return;
    }
}

vector<size_t>
make_histogram(struct Input data) {
    vector<size_t> bins(data.bin_count);
    double min=data.numbers[0];
    double max=data.numbers[0];
    find_minmax(data.numbers,min,max);
    for (double number:data.numbers){
        size_t bin=(size_t)((number-min)/(max-min)*data.bin_count);
        if (bin==data.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
        return bins;
}
