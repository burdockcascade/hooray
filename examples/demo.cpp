#include <hooray.hpp>
#include <memory>

namespace {
    struct RectController : Hooray::NodeController<Hooray::RectangleShape> {

        void OnUpdate(float dt, Hooray::RectangleShape &rect) override {
            // do something
        }

    };
}

int main() {
    return Hooray::RunApp({
        .window = {
            .title = "Hooray Demo",
            .width = 800,
            .height = 600,
            .targetFps = 60
        },
        .scenes = {
            Hooray::Scene {
                .layers = {
                    Hooray::Layer2D {
                        .camera = {
                            .target = {.x = 0.0f, .y = 0.0f},
                            .offset = {.x = 400.0f, .y = 300.0f},
                            .rotation = 0.0f,
                            .zoom = 1.0f
                        },
                        .elements = {
                            Hooray::RectangleShape {
                                .position = {.x = 10.0f, .y = 10.0f},
                                .size = {.x = 200.0f, .y = 150.0f},
                                .fillColor = Hooray::Colors::Red,
                                .controller = std::make_shared<RectController>()
                            },
                            Hooray::CircleShape {
                                .position = {.x = 40.0f, .y = 30.0f},
                                .radius = 75.0f,
                                .fillColor = Hooray::Colors::Green,
                                .controller = Hooray::NodeCallbacks<Hooray::CircleShape>{
                                    .onUpdate = [](float dt, Hooray::CircleShape &circle) {
                                        // do something
                                    }
                                }
                            },
                            Hooray::TriangleShape {
                                .position = {.x = 60.0f, .y = 40.0f},
                                .size = 100.0f,
                                .fillColor = Hooray::Colors::Blue
                            }
                        }
                    }
                }
            }
        }
    });
}
