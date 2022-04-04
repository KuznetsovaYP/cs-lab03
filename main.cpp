#include <iostream>
#include<vector>

using namespace std;

const size_t SCREEN_WIDTE=80;
const size_t MAX_ASTERISK=SCREEN_WIDTE-3-1;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void
find_minmax(const vector<double> &numbers, double& min, double& max) {
    min = numbers[0];
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

void
show_histogram_text(const vector<size_t> &bins) {
    size_t max_bin=bins[0];

        for(size_t bin: bins)
        {
            if(max_bin<bin)
            {
                max_bin=bin;
            }
        }

    for(size_t bin:bins)
        {
            size_t height=bin;

            if(max_bin>MAX_ASTERISK)
            {
                height=MAX_ASTERISK*(static_cast<double>(bin)/max_bin);
            }

            if (bin<100)
            {
                cout<<" ";
            }

            if (bin<10)
            {
                cout<<" ";
            }
            cout<<bin<<"|";
            for(size_t i=0; i<height; i++)
            {
                cout<<"*";
            }
            cout<<endl;

        }
        return;
}

int main()
{
//Ввод данных

    size_t number_count;
    cerr<<"Enter number count:";
    cin>>number_count;

    cerr<<"Enter numbers:";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;

        cerr<<"Enter bin count:";
        cin>>bin_count;
//Расчет гистограммы

        double min=numbers[0];
        double max=numbers[0];

        find_minmax(numbers,min,max);

        double bin_size = (max-min) / bin_count;
        const auto bins = make_histogram(numbers, bin_count,number_count,bin_size,min );


//Вывод данных


        show_histogram_text(bins);





    return 0;
}
