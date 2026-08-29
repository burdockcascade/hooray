#include "hooray.hpp"

namespace {

    class SimpleApp : public Hooray::Application {

    public:
        SimpleApp() : Hooray::Application(900, 700, "2D Orbiting Neon Swarm") {}

        void on_init() override {
            // Initialization logic can be added here
        }

        void on_update(float delta_time) override {
            // Update logic can be added here
        }

        void on_draw(Hooray::Renderer& render) override {
            render.clearBackground(Hooray::Palette::CharBlack);

            render.withScreenSpace([](Hooray::Layer2d layer) {
                layer.drawText("Hello, World");
            });
        }
    };
}

int main() {
    SimpleApp app;
    app.run();
    return 0;
}