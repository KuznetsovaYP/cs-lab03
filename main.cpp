#include "input.h"
#include "histogram.h"
#include "svg.h"
#include <iostream>
#include<vector>
#include <curl/curl.h>
#include <sstream>
#include <string>


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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size;
    data_size=item_count*item_size;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    const char* items2 = reinterpret_cast<const char*>(items);
    buffer->write(items2, data_size);
    return 0;
}

Input
download(const string& address) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
        if(curl) {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL,address.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
            if(res )
                {
                    cout <<  curl_easy_strerror(res);
                    exit(1);
                }
            curl_easy_cleanup(curl);
            }

    return read_input(buffer, false);
}



int main(int argc, char* argv[])
{
    Input input;

    if (argc>1)
    {
        input=download(argv[1]);
    }
    else
    {
        input=read_input(cin,true);
    }

    //Расчет гистограммы

    const auto bins = make_histogram(input);
    int c;
    c=0;


    for ( int i=0;i<argc;i++)
    {
        if (argv[i]=="-stroke")
        {
                show_histogram_svg(bins,argv[i+1]);
                c++;
        }
    }
    if (c==0)
        show_histogram_svg(bins,"darkmagenta");


    return 0;
}
