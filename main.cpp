#include "input.h"
#include "histogram.h"
#include "svg.h"
#include <iostream>
#include<vector>
#include <windows.h>
#include <sstream>

using namespace std;


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

string make_info_text()
{
    stringstream buffer;
   DWORD WINAPI GetVersion(void);
    DWORD info= GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD platform = info >> 16;
    DWORD build;
    DWORD version = info & mask;
    DWORD version_major = version & 0xff;
    DWORD version_minor = version >> 8;
    if ((info & 0b10000000'00000000'0000000'00000000) == 0)
    {
    build = platform;
    }
    else
    printf("minor_bit = %u",1);
    char computer_name [MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(computer_name);
    GetComputerNameA(computer_name, &Size);

    buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << " " << "Computer name: " << computer_name;
    return buffer.str();
}


int main()
{

//Ввод данных

    size_t number_count;
    cerr<<"Enter number count:";
    cin>>number_count;

    cerr<<"Enter numbers:";
    const auto numbers = input_numbers(number_count,cin);

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

        size_t bin_height;
        show_histogram_svg(bins,bin_height,make_info_text());




    return 0;
}
