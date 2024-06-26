#include <stddef.h>
#include <string>
#include <vector>
#include <gdkmm/rgba.h>
#include <cairomm/context.h>

using namespace std;
using namespace Gdk;
using namespace Gtk;

class coord_pair {

    public:
    size_t x;
    size_t y;

    coord_pair(size_t x = 0, size_t y = 0) : x(x), y(y) {}
};

class DataSeries
{
    public:

    vector<coord_pair> data_points = vector<coord_pair>(0); // Defaults to a series with no points.
    size_t point_size;
    Gdk::RGBA point_color = Gdk::RGBA(0, 0, 0, 1); // Defaults to white.
    
    /**
     * @brief Draws the data series on the graph.
     * 
     * @param cr 
     */
    void draw_series(const Cairo::RefPtr<Cairo::Context>& cr) {
        cr->set_source_rgba(point_color.get_red_u(), point_color.get_green_u(), point_color.get_blue_u(), point_color.get_alpha_u());
        for (auto point : data_points)
        {
            cr->arc(point.x, point.y, point_size, 0, 2 * M_PI);
            cr->fill();
        }
        cr->stroke();
    }
};


class Line {

    public:
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
    public:
    string axis_label;
    size_t index_marker_spacing;

    Axis() : Line(coord_pair(0, 0), coord_pair(0, 0)) {}
};