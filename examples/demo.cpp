#include <hooray.hpp>

int main() {
    return Hooray::RunApp({
        .window = {
            .title = "Hooray Demo",
            .width = 800,
            .height = 600,
            .flags = {
                .resizable = true,
                .fullscreen = false,
                .vsync = true,
            },
            .targetFps = 60,
            .showFPS = true
        },
        .assets = {
            Hooray::FontAsset{
                .id = "font1",
                .path = R"(..\..\examples\assets\Roboto-Regular.ttf)",
                .baseSize = 64
            },
            Hooray::MusicAsset{
                .id = "music1",
                .path = R"(..\..\examples\assets\music1.mp3)"
            },
            Hooray::MusicAsset{
                .id = "music2",
                .path = R"(..\..\examples\assets\music2.mp3)"
            }
        },
        .scenes = {
            Hooray::Scene {
                .music = {
                    Hooray::MusicStream {
                        .audio_id = "music2",
                        .looping = true,
                        .volume = 0.5f
                    }
                },
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
                                .fillColor = Hooray::Colors::Red,
                                .controller = Hooray::NodeCallbacks<Hooray::RectangleShape>{
                                    .onKeyEvent = [](const Hooray::KeyEvent& event, Hooray::RectangleShape& shape) {
                                        if (event.key == Hooray::Key::Enter) {
                                            shape.transform.rotation += 5.0f;
                                        }
                                    }
                                }
                            },
                            Hooray::Group {
                                .transform = {
                                    .position = {.x = 300.0f, .y = 200.0f},
                                },
                                .elements = {
                                    Hooray::CircleShape {
                                        .transform = {
                                            .position = {.x = 40.0f, .y = 30.0f},
                                        },
                                        .radius = 75.0f,
                                        .fillColor = Hooray::Colors::Green,
                                    },
                                    Hooray::TriangleShape {
                                        .transform = {
                                            .position = {.x = 60.0f, .y = 40.0f},
                                        },
                                        .p1 = {.x = 0.0f, .y = -50.0f},
                                        .p2 = {.x = -50.0f, .y = 50.0f},
                                        .p3 = {.x = 50.0f, .y = 50.0f},
                                        .fillColor = Hooray::Colors::Blue,
                                    },
                                },
                                .controller = Hooray::NodeCallbacks<Hooray::Group> {
                                    .onKeyEvent = [](const Hooray::KeyEvent& event, Hooray::Group& shape) {
                                        if (event.action == Hooray::KeyAction::Pressed && event.key == Hooray::Key::Space) {
                                            shape.visible = !shape.visible;
                                        }
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
                            },
                        }
                    },
                    Hooray::LayerUI {
                        .elements = {
                            Hooray::Text {
                                .text = "Hello, Hooray!",
                                .font_id = "font1",
                                .transform = {
                                    .position = {.x = 50.0f, .y = 50.0f},
                                },
                                .color = Hooray::Colors::Black,
                            }
                        }
                    }
                }
            }
        }
    });
}
