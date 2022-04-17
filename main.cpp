#include "histogram.h"
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
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>"<< text <<"</text>";
}

void svg_rect(double x, double y, double width, double height,string stroke="darkmagenta", string fill="lightcyan"){
    cout<< "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

void
show_histogram_svg(const vector<size_t>& bins, size_t& bin_height) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    size_t max_count=0;
    for (size_t count : bins){
        if (count>max_count)
        {
            max_count=count;
        }
    }
    const bool scaling_needed=(max_count>MAX_ASTERISK);
    if(scaling_needed)
    {
        const double scaling_factor=MAX_ASTERISK/(double)max_count;
        for (size_t bin : bins)
        {
            const double height=(double)bin*scaling_factor;
            const double bin_width=BLOCK_WIDTH*height;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top += BIN_HEIGHT;
        }
    }
    else
    {
        for (size_t bin : bins)
        {
            const double bin_width=static_cast<double>(BLOCK_WIDTH*bin);
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
        }
    }
    svg_end();
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

        size_t bin_height;
        show_histogram_svg(bins,bin_height);




    return 0;
}
