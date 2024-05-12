#include <stddef.h>

class coord_pair {
    size_t x;
    size_t y;

    coord_pair(size_t x, size_t y) : x(x), y(y) {}
};


class Line {
    coord_pair start;
    coord_pair end;
    size_t stroke_width;

    Line(coord_pair start, coord_pair end) : start(start), end(end) {}

    void draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        cr->set_line_width(stroke_width);
        cr->move_to(start.x, start.y);
        cr->line_to(end.x, end.y);
        cr->stroke();
    }

    void set_stroke_width(size_t width) {
        stroke_width = width;
    }

};

class Axis : public Line 
{
    
}