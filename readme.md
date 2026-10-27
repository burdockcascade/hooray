# Hooray

## Features
* 2d and UI scenegraph
* Audio playback
* Input handling
* Cross-platform (Windows, Linux, MacOS)

## Example
```cpp
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
                                .fillColor = Hooray::Colors::Blue,
                                .controller = Hooray::NodeCallbacks<Hooray::TriangleShape> {
                                    .onKeyEvent = [](const Hooray::KeyEvent& event, Hooray::TriangleShape& shape) {
                                        if (event.action == Hooray::KeyAction::Down && event.key == Hooray::Key::Right) {
                                            shape.transform.position.x += 1.0f;
                                        }
                                        if (event.action == Hooray::KeyAction::Down && event.key == Hooray::Key::Left) {
                                            shape.transform.position.x -= 1.0f;
                                        }
                                        if (event.action == Hooray::KeyAction::Down && event.key == Hooray::Key::Up) {
                                            shape.transform.position.y -= 1.0f;
                                        }
                                        if (event.action == Hooray::KeyAction::Down && event.key == Hooray::Key::Down) {
                                            shape.transform.position.y += 1.0f;
                                        }
                                        if (event.action == Hooray::KeyAction::Down && event.key == Hooray::Key::R) {
                                            shape.transform.rotation += 5.0f;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    });
}

```