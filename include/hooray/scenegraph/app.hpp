#pragma once
#include <vector>

#include "assets.hpp"
#include "color.hpp"
#include "controller.hpp"
#include "node2d.hpp"

namespace Hooray {

    struct Camera2D {
        bool active{true};
        bool visible{true};
        Vector2 target{.x = 0.0f, .y = 0.0f};
        Vector2 offset{.x = 0.0f, .y = 0.0f};
        float rotation{0.0f};
        float zoom{1.0f};
        ControllerSlot<Camera2D> controller{};
    };

    struct LayerUI {
        bool active{true};
        bool visible{true};
        std::vector<VisualElement2D> elements{};
    };

    struct Layer2D {
        bool active{true};
        bool visible{true};
        Camera2D camera{};
        std::vector<VisualElement2D> elements{};
    };

    struct Layer3D {
        // Placeholder for future 3D layer implementation
        bool active{true};
        bool visible{true};
    };

    using Layer = std::variant<LayerUI, Layer2D, Layer3D>;

    struct Scene {
        bool active{true};
        bool visible{true};
        std::vector<Layer> layers{};
    };

    struct WindowFlags {
        bool resizable{false};
        bool fullscreen{false};
        bool vsync{true};
    };

    struct WindowConfig {
        std::string title = "Hooray App";
        int width = 1280;
        int height = 720;
        Color bgColor{Colors::White};
        WindowFlags flags{};
        int targetFps = 60;
        bool showFPS{false};
    };

    struct AppConfig {
        WindowConfig window{};
        std::vector<Asset> assets{};
        std::vector<Scene> scenes{};
    };

}
