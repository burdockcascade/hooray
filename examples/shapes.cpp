#include <hooray.hpp>

int main() {

    // Create a rectangle shape
    hooray::RectangleShape rect;
    rect.set_transform({
        .position = {.x = 10.0f, .y = 10.0f},
        .rotation = 0.0f,
        .scale = {.x = 1.0f, .y = 1.0f}
    });
    rect.set_size(200.0f, 150.0f);
    rect.set_fill_color(hooray::colors::RED);

    // Create a circle shape
    hooray::CircleShape circle;
    circle.set_transform({
        .position = {.x = 40.0f, .y = 30.0f},
        .rotation = 0.0f,
        .scale = {.x = 1.0f, .y = 1.0f}
    });
    circle.set_radius(75.0f);
    circle.set_fill_color(hooray::colors::GREEN);

    // Create a triangle shape
    hooray::TriangleShape triangle;
    triangle.set_transform({
        .position = {.x = 60.0f, .y = 40.0f},
        .rotation = 0.0f,
        .scale = {.x = 1.0f, .y = 1.0f}
    });
    triangle.set_points(hooray::Vector2{.x = 0.0f, .y = -50.0f}, hooray::Vector2{.x = -50.0f, .y = 50.0f}, hooray::Vector2{.x = 50.0f, .y = 50.0f});
    triangle.set_fill_color(hooray::colors::BLUE);

    // Create a camera for the layer
    hooray::Camera2D cam;
    cam.set_target(0.0f, 0.0f);
    cam.set_offset(400.0f, 300.0f);
    cam.set_rotation(0.0f);
    cam.set_zoom(1.0f);

    // Create a layer and add the shapes to it
    hooray::Layer2D layer;
    layer.set_camera(cam);
    layer.add_element(rect);
    layer.add_element(circle);
    layer.add_element(triangle);

    // Create a scene and add the layer to it
    hooray::Scene main_scene;
    main_scene.add_layer(layer);

    // Create the application and configure it
    hooray::App app;
    app.set_title("hooray Shapes Demo");
    app.set_fps_target(60);
    app.set_window_size(800, 600);
    app.set_background_color(hooray::colors::SKY_BLUE);
    app.add_scene(main_scene);

    return app.run();

}
