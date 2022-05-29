#include "svg.h"
#include <iostream>

const size_t SCREEN_WIDTE=80;
const size_t MAX_ASTERISK=SCREEN_WIDTE-3-1;

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

void svg_rect(double x, double y, double width, double height,string stroke, string fill){
    cout<< "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

void
show_histogram_svg(const vector<size_t>& bins, string stroke) {
    size_t height;
    if(bins.size()==0)
    {
        return;
    }
    const auto IMAGE_WIDTH = 400;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 20;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    size_t max_count=bins[0];
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
        const double IMAGE_HEIGHT=(double)max_count*scaling_factor*BLOCK_WIDTH+200;
        svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
        for (size_t bin : bins)
        {
            height=(double)bin*scaling_factor;
            const double bin_width=BLOCK_WIDTH*height;
            svg_text(top+TEXT_LEFT, TEXT_BASELINE+(IMAGE_HEIGHT-200)+30, to_string(bin));
            svg_rect(top+10,TEXT_WIDTH+(IMAGE_HEIGHT-200)-bin_width,BIN_HEIGHT, bin_width, stroke);
            top += BIN_HEIGHT;
        }
    }
    else
    {
        const double IMAGE_HEIGHT=static_cast<double>(BLOCK_WIDTH*max_count+200);
        svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
        for (size_t bin : bins)
        {
            height=bin;
            const double bin_width=static_cast<double>(BLOCK_WIDTH*height);
            svg_text(top+TEXT_LEFT, TEXT_BASELINE+(IMAGE_HEIGHT-200)+30, to_string(bin));
            svg_rect(top+10,TEXT_WIDTH+(IMAGE_HEIGHT-200)-bin_width,BIN_HEIGHT, bin_width, stroke);
            top += BIN_HEIGHT;
        }
    }
    svg_end();
}
