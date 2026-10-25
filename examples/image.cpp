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
                        .elements = {
                            Hooray::Sprite{
                                .visible = false,
                                .texture_id = "sample_img1",
                                .transform = {
                                    .position = {.x = 0.0f, .y = 10.0f}
                                }
                            },
                            Hooray::Sprite{
                                .visible = true,
                                .texture_id = "sample_img2",
                                .transform = {
                                    .position = {.x = 0.0f, .y = 0.0f},
                                    .scale = {.x = 0.5f, .y = 0.5f}
                                }
                            },
                            Hooray::Sprite{
                                .visible = false,
                                .texture_id = "bird_img",
                                .transform = {
                                    .position = {.x = 0.0f, .y = 0.0f}
                                }
                            }
                        }
                    }
                }
            }
        }
    });
}
