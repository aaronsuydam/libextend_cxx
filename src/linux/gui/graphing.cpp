#include <gtkmm/application.h>
#include <CPU_StatsGraph.hpp>

using namespace Gtk;
using namespace std;

int main(int argc, char** argv)
{
    auto app = Application::create("graphing.example.test");

    GraphingWindow window;

    return app->make_window_and_run<GraphingWindow>(window);
}