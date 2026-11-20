#include <iostream>
#include <hooray/core/app.hpp>
#include <hooray/scenegraph/scene.hpp>

class MySceneController : public hooray::Controller<hooray::Scene> {
public:
    void on_window_event(hooray::Scene &node, hooray::WindowEvent &event) override {
        std::cout << "Window event: " << event.action;

        if (event.action == hooray::WindowAction::RESIZED ||
            event.action == hooray::WindowAction::MAXIMIZED ||
            event.action == hooray::WindowAction::UNMAXIMIZED) {
            std::cout << " (" << event.width << "x" << event.height << ")";
            }

        std::cout << '\n';
    }
};

int main() {

    // Create a scene and add the layer to it (use std::move here)
    hooray::Scene main_scene;
    main_scene.set_controller(MySceneController());

    // Create the application and configure it
    hooray::App app;
    app.set_title("hooray Window Demo");
    app.set_fps_target(60);
    app.draw_fps(true);
    app.set_window_size(800, 600);
    app.set_background_color(hooray::colors::SKY_BLUE);
    app.set_resizable(true);
    app.add_scene(main_scene);

    // Run the application
    return app.run();
}
