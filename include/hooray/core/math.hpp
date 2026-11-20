#pragma once

namespace hooray {

    struct Vector2 {
        float x{0.0f};
        float y{0.0f};
    };

    struct Transform2D {
        Vector2 position{.x = 0.0f, .y = 0.0f};
        float rotation{0.0f}; // in degrees
        Vector2 scale{.x = 1.0f, .y = 1.0f};
        Vector2 origin{.x = 0.0f, .y = 0.0f};
    };

}