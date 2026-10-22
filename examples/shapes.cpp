#include <hooray.hpp>

int main() {
    return Hooray::RunApp({
        .window = {
            .title = "Hooray Shapes Demo",
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
                                .fillColor = Hooray::Colors::Red
                            },
                            Hooray::CircleShape {
                                .position = {.x = 40.0f, .y = 30.0f},
                                .radius = 75.0f,
                                .fillColor = Hooray::Colors::Green
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
