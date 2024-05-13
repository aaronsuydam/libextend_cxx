#include <gtkmm/application.h>
#include "GraphArea.hpp"

using namespace Gtk;
using namespace std;

int main(int argc, char** argv)
{
    auto app = Application::create("graphing.example.test");


    return app->make_window_and_run<GraphingWindow>(argc, argv);
}