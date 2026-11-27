#pragma once

#include <variant>
#include <vector>
#include "hooray/core/color.hpp"
#include "hooray/core/math.hpp"
#include "hooray/core/assets.hpp"

namespace hooray {

    // --- State & Camera Commands ---
    struct BeginCamera2DCmd {
        Vector2 offset{};
        Vector2 target{};
        float rotation{0.0f};
        float zoom{1.0f};
    };

    struct EndCamera2DCmd {};

    struct PushTransformCmd {
        Transform2D transform{};
    };

    struct PopTransformCmd {};

    // --- Primitive & Texture Commands ---
    struct DrawTextureCmd {
        TextureHandle texture{};
        TextureRegion source{};
        TextureRegion dest{};
        Vector2 origin{};
        float rotation{0.0f};
        Color tint{colors::WHITE};
    };

    struct DrawRectCmd {
        Vector2 position{};
        Vector2 size{};
        Vector2 origin{};
        float rotation{0.0f};
        Color color{colors::WHITE};
    };

    struct DrawCircleCmd {
        Vector2 center{};
        float radius{0.0f};
        Color color{colors::WHITE};
    };

    struct DrawTriangleCmd {
        Vector2 p1{};
        Vector2 p2{};
        Vector2 p3{};
        Color color{colors::WHITE};
    };

    struct DrawPolygonCmd {
        std::vector<Vector2> points{};
        Color color{colors::WHITE};
        bool wireframe{false};
        float line_thickness{1.0f};
    };

    // Variant holding all possible render commands
    using RenderCommand = std::variant<
        BeginCamera2DCmd,
        EndCamera2DCmd,
        PushTransformCmd,
        PopTransformCmd,
        DrawTextureCmd,
        DrawRectCmd,
        DrawCircleCmd,
        DrawTriangleCmd,
        DrawPolygonCmd
    >;

    // Helper buffer passed down the scenegraph during traversal
    class RenderCommandList {
    public:
        void clear() noexcept { commands_.clear(); }
        void reserve(size_t capacity) { commands_.reserve(capacity); }

        template <typename CmdT, typename... Args>
        void emplace(Args&&... args) {
            commands_.emplace_back(std::in_place_type<CmdT>, std::forward<Args>(args)...);
        }

        void push(RenderCommand cmd) {
            commands_.push_back(std::move(cmd));
        }

        [[nodiscard]] const std::vector<RenderCommand>& commands() const noexcept {
            return commands_;
        }

    private:
        std::vector<RenderCommand> commands_;
    };

}