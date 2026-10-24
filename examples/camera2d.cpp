#include <hooray.hpp>
#include <memory>

namespace {
    struct MyCameraController : Hooray::NodeController<Hooray::Camera2D> {

        float speed = 4.0f;
        float stepDistance = 32.0f; // Distance jumped per step
        float zoomStep = 0.05f;
        bool shiftPressed = false;

        void OnKeyEvent(const Hooray::KeyEvent& event, Hooray::Camera2D& camera) override {

            // Track Shift state
            if (event.key == Hooray::Key::LeftShift || event.key == Hooray::Key::RightShift) {
                if (event.action == Hooray::KeyAction::Pressed || event.action == Hooray::KeyAction::Down) {
                    shiftPressed = true;
                } else if (event.action == Hooray::KeyAction::Released) {
                    shiftPressed = false;
                }
            }

            // Continuous movement while held (only when Shift is NOT held)
            if (!shiftPressed && event.action == Hooray::KeyAction::Down) {
                if (event.key == Hooray::Key::Up)    camera.target.y -= speed;
                if (event.key == Hooray::Key::Down)  camera.target.y += speed;
                if (event.key == Hooray::Key::Left)  camera.target.x -= speed;
                if (event.key == Hooray::Key::Right) camera.target.x += speed;
                if (event.key == Hooray::Key::P)     camera.zoom += 0.01f;
                if (event.key == Hooray::Key::O)     camera.zoom -= 0.01f;
            }

            // Stepped movement: trigger once per press when Shift is active
            if (shiftPressed && event.action == Hooray::KeyAction::Pressed) {
                if (event.key == Hooray::Key::Up)    camera.target.y -= stepDistance;
                if (event.key == Hooray::Key::Down)  camera.target.y += stepDistance;
                if (event.key == Hooray::Key::Left)  camera.target.x -= stepDistance;
                if (event.key == Hooray::Key::Right) camera.target.x += stepDistance;
                if (event.key == Hooray::Key::P)     camera.zoom += zoomStep;
                if (event.key == Hooray::Key::O)     camera.zoom -= zoomStep;
            }

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
                            .zoom = 1.0f,
                            .controller = std::make_shared<MyCameraController>()
                        },
                        .elements = {
                            Hooray::RectangleShape {
                                .transform = {
                                    .position = {.x = 10.0f, .y = 10.0f},
                                },
                                .size = {.x = 200.0f, .y = 150.0f},
                                .fillColor = Hooray::Colors::Red
                            },
                            Hooray::CircleShape {
                                .transform = {
                                    .position = {.x = 40.0f, .y = 30.0f},
                                },
                                .radius = 75.0f,
                                .fillColor = Hooray::Colors::Green,
                                .controller = Hooray::NodeCallbacks<Hooray::CircleShape>{
                                    .onKeyEvent = [](const Hooray::KeyEvent& event, Hooray::CircleShape& circle) {
                                        if (event.key == Hooray::Key::Enter) {
                                            circle.radius += 5.0f;
                                        }
                                    }
                                }
                            },
                            Hooray::TriangleShape {
                                .transform = {
                                    .position = {.x = 60.0f, .y = 40.0f},
                                },
                                .size = 100.0f,
                                .fillColor = Hooray::Colors::Blue
                            }
                        }
                    },
                    Hooray::LayerUI {
                        .elements = {
                        Hooray::RectangleShape {
                                .transform = {
                                    .position = {.x = 10.0f, .y = 10.0f},
                                },
                                .size = {.x = 200.0f, .y = 150.0f},
                                .fillColor = Hooray::Colors::Red
                            },
                            Hooray::CircleShape {
                                .transform = {
                                    .position = {.x = 40.0f, .y = 30.0f},
                                },
                                .radius = 75.0f,
                                .fillColor = Hooray::Colors::Green
                            },
                            Hooray::TriangleShape {
                                .transform = {
                                    .position = {.x = 60.0f, .y = 40.0f},
                                },
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
