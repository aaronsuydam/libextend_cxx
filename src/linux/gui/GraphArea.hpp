#include <vector>

#include <gtkmm/drawingarea.h>
#include "util.hpp"

class GraphArea : public Gtk::DrawingArea
{

    public:


    GraphArea();
    Axis x_axis;
    Axis y_axis;
    vector<DataSeries> data;
    
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int height, int width);

};