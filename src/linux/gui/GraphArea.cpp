#include "GraphArea.hpp"

GraphArea::GraphArea()
{
    x_axis = Axis();
    y_axis = Axis();
    data = DataSeries();

    x_axis.set_stroke_width(2);
    y_axis.set_stroke_width(2);
}

void GraphArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int height, int width)
{

    x_axis.draw(cr);
    y_axis.draw(cr);
    for (auto series : data)
    {
        series.draw_series(cr);
    }
}