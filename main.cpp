#include "input.h"
#include "histogram.h"
#include "svg.h"
#include <iostream>
#include<vector>
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>

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
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;

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


int main(int argc, char* argv[])
{
    Input input;

//Ввод данных

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
                show_histogram_svg(bins,argv[i+1],make_info_text());
                c++;
        }
    }
    if (c==0)
        show_histogram_svg(bins,"darkmagenta",make_info_text());


    return 0;
}
