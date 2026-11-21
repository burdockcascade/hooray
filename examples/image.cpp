#include <hooray.hpp>

int main() {

    // Create an image sprite
    hooray::Image2D image;
    image.set_texture_id("sample_img1");
    image.set_transform({
        .position = {.x = 50.0f, .y = 10.0f},
        .rotation = 0.0f,
        .scale = {.x = 1.0f, .y = 1.0f}
    });

    // Create a layer and add the shapes to it
    hooray::Layer2D layer;
    layer.add_element(image);

    // Create a scene and add the layer to it
    hooray::Scene main_scene;
    main_scene.add_layer(layer);

    // Create the application and configure it
    hooray::App app;
    app.set_title("hooray Shapes Demo");
    app.set_fps_target(60);
    app.set_window_size(800, 600);
    app.set_background_color(hooray::colors::SKY_BLUE);

    app.get_asset_manager().queue_texture({
        .id = "sample_img1",
        .path = R"(..\..\examples\assets\sample1.png)"
    });

    app.add_scene(main_scene);

    return app.run();

}
