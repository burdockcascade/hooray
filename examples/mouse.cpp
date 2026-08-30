#include <iostream>

#include "hooray.hpp"

namespace {

    constexpr auto text_pos = Hooray::Vector2{10.0f, 10.0f};

    class SimpleApp : public Hooray::Application {

    public:
        SimpleApp() : Hooray::Application(900, 700, "Mouse Position Tracker") {}

        void on_init() override {
            mouse_position_ = Hooray::Vector2{10, 10};
        }

        void on_mouse_moved(Hooray::Vector2 vector2) override {
            mouse_position_ = vector2;
        }

        void on_update(float delta_time) override {
            // Update logic can be added here
        }

        void on_draw(Hooray::Renderer &render) override {
            render.clearBackground(Hooray::Palette::CharBlack);

            render.withScreenSpace([this](Hooray::Layer2d layer) {
                layer.drawText("Mouse Pos; X: " + std::to_string(mouse_position_.x) + " Y: " + std::to_string(mouse_position_.y), text_pos);
            });
        }

    private:
        Hooray::Vector2 mouse_position_;
    };


}

int main() {
    SimpleApp app;
    app.run();
    return 0;
}