#include "../svg.h"

#include <cassert>

void
test_big()
{
    size_t height;
    show_histogram_svg({100,210,421},height);
    assert(height<=80);
}

void
test_empty()
{
 size_t height;
 show_histogram_svg({},height);
}
int
main() {
    test_big();
    test_empty();
}
