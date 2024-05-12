#include <gtkmm/drawingarea.h>


class GraphArea : public Gtk::DrawingArea
{

public:
    GraphArea();
    
    
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int height, int width);

};