#pragma once
#include <string>
#include "math.hpp"
#include "color.hpp"
#include "controller.hpp"

namespace Hooray {

    struct Transform2D {
        Vector2 position{.x = 0.0f, .y = 0.0f};
        float rotation{0.0f}; // in degrees
        Vector2 scale{.x = 1.0f, .y = 1.0f};
        Vector2 origin{.x = 0.0f, .y = 0.0f};
    };

    struct RectangleShape {
        bool active{true};
        bool visible{true};
        Transform2D transform{};
        Vector2 size{.x = 100.0f, .y = 100.0f};
        Color fillColor{Colors::White};
        Color strokeColor{Colors::Transparent};
        float strokeWidth{0.0f};
        float roundness{0.0f};
        int segments{8};
        ControllerSlot<RectangleShape> controller{};
    };

    struct CircleShape {
        bool active{true};
        bool visible{true};
        Transform2D transform{};
        float radius{50.0f};
        Color fillColor{Colors::White};
        Color strokeColor{Colors::Transparent};
        float strokeWidth{0.0f};
        ControllerSlot<CircleShape> controller{};
    };

    struct RingShape {
        bool active{true};
        bool visible{true};
        Transform2D transform{};
        float innerRadius{20.0f};
        float outerRadius{40.0f};
        float startAngle{0.0f};      // In degrees
        float endAngle{360.0f};      // In degrees
        int segments{36};
        Color fillColor{Colors::White};
        ControllerSlot<RingShape> controller{};
    };

    struct TriangleShape {
        bool active{true};
        bool visible{true};
        Transform2D transform{};
        Vector2 p1{.x = 0.0f, .y = -25.0f};
        Vector2 p2{.x = -25.0f, .y = 25.0f};
        Vector2 p3{.x = 25.0f, .y = 25.0f};
        Color fillColor{Colors::White};
        Color strokeColor{Colors::Transparent};
        ControllerSlot<TriangleShape> controller{};
    };

    struct EllipseShape {
        bool active{true};
        bool visible{true};
        Transform2D transform{};
        Vector2 radius{.x = 50.0f, .y = 25.0f};
        Color fillColor{Colors::White};
        Color strokeColor{Colors::Transparent};
        ControllerSlot<EllipseShape> controller{};
    };

    struct LineShape {
        bool active{true};
        bool visible{true};
        Transform2D transform{};
        Vector2 start{.x = 0.0f, .y = 0.0f};
        Vector2 end{.x = 100.0f, .y = 0.0f};
        float thickness{2.0f};
        Color color{Colors::White};
        ControllerSlot<LineShape> controller{};
    };

    struct Text {
        bool active{true};
        bool visible{true};
        std::string text;
        std::string font_id;      // Empty string falls back to Raylib's default font
        Transform2D transform{};
        mutable float fontSize{0.0f};
        float spacing{1.0f};          // Spacing between characters
        Color color{Colors::White};
        ControllerSlot<Text> controller{};
    };

    struct Sprite {
        bool active{true};
        bool visible{true};
        std::string texture_id;
        Transform2D transform{};
        Vector2 size{0.0f, 0.0f};
        Color tint{Colors::White};
        ControllerSlot<Sprite> controller{};
    };

    struct Group;
    using VisualElement2D = std::variant<
        Group,
        RectangleShape,
        CircleShape,
        TriangleShape,
        LineShape,
        EllipseShape,
        RingShape,
        Sprite,
        Text
    >;

    struct Group {
        bool active{true};
        bool visible{true};
        Transform2D transform{};
        std::vector<VisualElement2D> elements{};
        ControllerSlot<Group> controller{};
    };

}
