#pragma once

#include <algorithm>
#include <vector>

#include "math.hpp"

namespace Hooray {

    class Rectangle {
    public:
        float x{0.0f};
        float y{0.0f};
        float width{0.0f};
        float height{0.0f};

        constexpr Rectangle() noexcept = default;
        constexpr Rectangle(float x_, float y_, float width_, float height_) noexcept: x{x_}, y{y_}, width{width_}, height{height_} {}
        constexpr Rectangle(Vector2 position, Vector2 size) noexcept: x{position.x}, y{position.y}, width{size.x}, height{size.y} {}

        [[nodiscard]] constexpr Vector2 get_position() const noexcept { return {x, y}; }
        constexpr void set_position(Vector2 pos) noexcept { x = pos.x; y = pos.y; }

        [[nodiscard]] constexpr Vector2 get_size() const noexcept { return {width, height}; }
        constexpr void set_size(Vector2 size) noexcept { width = size.x; height = size.y; }

        [[nodiscard]] constexpr float left() const noexcept { return x; }
        [[nodiscard]] constexpr float right() const noexcept { return x + width; }
        [[nodiscard]] constexpr float top() const noexcept { return y; }
        [[nodiscard]] constexpr float bottom() const noexcept { return y + height; }
        [[nodiscard]] constexpr Vector2 center() const noexcept { return {x + width * 0.5f, y + height * 0.5f}; }

        [[nodiscard]] bool contains(Vector2 point) const noexcept;
        [[nodiscard]] bool overlaps(Rectangle other) const noexcept;
        [[nodiscard]] Rectangle get_collision(Rectangle other) const noexcept;

        constexpr bool operator==(const Rectangle& rhs) const noexcept {
            return x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height;
        }

    };

    struct Circle {
        Vector2 center;
        float radius;

        constexpr Circle() noexcept = default;
        constexpr Circle(Vector2 center_, float radius_) noexcept : center{center_}, radius{radius_} {}
        constexpr Circle(float x, float y, float radius_) noexcept : center{x, y}, radius{radius_} {}

        [[nodiscard]] bool contains(Vector2 other) const;
        [[nodiscard]] bool overlaps(Circle other) const;
        [[nodiscard]] bool overlaps(Rectangle other) const;
    };

    struct JSTriangle {
        Vector2 v1;
        Vector2 v2;
        Vector2 v3;
    };

    struct JSPoint {
        Vector2 position;
    };

    struct JSLine {
        Vector2 start;
        Vector2 end;
    };

    struct JSPolygon {
        std::vector<Vector2> points;
    };

}