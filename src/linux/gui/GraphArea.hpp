#include <vector>

#include <gtkmm/drawingarea.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include "util.hpp"

using namespace std;
using namespace Gtk;

class GraphArea : public Gtk::DrawingArea
{

    public:


    GraphArea();
    Axis x_axis;
    Axis y_axis;
    vector<DataSeries> data;
    
    void draw(const Cairo::RefPtr<Cairo::Context>& cr, int height, int width);

};

class GraphingWindow : public Gtk::Window
{
    public:
    GraphArea graph_area;
    Box main_box;

    GraphingWindow();
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int height, int width);

};