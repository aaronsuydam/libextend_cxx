#include "GraphArea.hpp"
#include <iostream>

GraphArea::GraphArea()
{
    x_axis = Axis();
    y_axis = Axis();
    data = vector<DataSeries>(0);

    x_axis.set_stroke_width(2);
    y_axis.set_stroke_width(2);
}

void GraphArea::draw(const Cairo::RefPtr<Cairo::Context>& cr, int height, int width)
{
    x_axis.draw(cr);
    y_axis.draw(cr);
    for (auto series : data)
    {
        series.draw_series(cr);
    }
}

GraphingWindow::GraphingWindow()
{
    main_box = Box(Orientation::VERTICAL);
    main_box.set_spacing(10);

    graph_area.set_size_request(800, 600);
    graph_area.x_axis.axis_label = "X Axis";
    graph_area.y_axis.axis_label = "Y Axis";

    graph_area.x_axis.start = coord_pair(50, 550);
    graph_area.x_axis.end = coord_pair(750, 550);

    graph_area.y_axis.start = coord_pair(50, 50);
    graph_area.y_axis.end = coord_pair(50, 550);
    graph_area.set_draw_func(sigc::mem_fun(*this, &GraphingWindow::on_draw));

    main_box.append(graph_area);

    set_child(main_box);
}


void GraphingWindow::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int height, int width)
{
    std::cout << "Checking that this is called! " << std::endl;
    graph_area.draw(cr, height, width);
}