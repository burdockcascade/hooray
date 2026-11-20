#include <iostream>
#include <ostream>

#include <hooray.hpp>

int main() {

    hooray::App app;
    app.set_title("hooray Window Demo");
    app.set_fps_target(60);
    app.draw_fps(true);
    app.set_window_size(800, 600);
    app.set_background_color(hooray::colors::SKY_BLUE);
    app.set_resizable(true);

    return app.run();
}