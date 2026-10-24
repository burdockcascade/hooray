#include <hooray.hpp>

int main() {
    return Hooray::RunApp({
        .window = {
            .title = "Hooray Demo",
            .width = 800,
            .height = 600,
            .targetFps = 60
        },
        .assets = {
            Hooray::TextureAsset{
                .id = "sample_img1",
                .path = R"(..\..\examples\assets\sample1.png)"
            },
            Hooray::TextureAsset{
                .id = "sample_img2",
                .path = R"(..\..\examples\assets\sample2.jpg)"
            },
            Hooray::TextureAsset{
                .id = "bird_img",
                .path = R"(..\..\examples\assets\bird.jpg)"
            }
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
                            Hooray::Sprite{
                                .visible = false,
                                .texture_id = "sample_img1",
                                .transform = {
                                    .position = {.x = 10.0f, .y = 10.0f}
                                }
                            },
                            Hooray::Sprite{
                                .visible = true,
                                .texture_id = "sample_img2",
                                .transform = {
                                    .position = {.x = 30.0f, .y = 30.0f}
                                }
                            },
                            Hooray::Sprite{
                                .visible = false,
                                .texture_id = "bird_img",
                                .transform = {
                                    .position = {.x = 100.0f, .y = 100.0f}
                                }
                            }
                        }
                    }
                }
            }
        }
    });
}
