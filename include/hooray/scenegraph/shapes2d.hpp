#pragma once
#include <array>

#include "node.hpp"
#include "hooray/core/color.hpp"
#include "hooray/render/drawcommands.hpp"

namespace hooray {
    class Shape2D : public Node2D {
    public:
        ~Shape2D() override = default;

        void set_fill_color(const Color &color) {
            fill_color_ = color;
        }

        [[nodiscard]] Color get_fill_color() const {
            return fill_color_;
        }

    protected:
        Color fill_color_{colors::WHITE};
    };

    class RectangleShape : public Shape2D {
    public:
        ~RectangleShape() override = default;

        void set_size(const float width, const float height) {
            size_ = {.x = width, .y = height};
        }

        [[nodiscard]] Vector2 get_size() const {
            return size_;
        }

    protected:
        void on_draw(RenderCommandList &cmds) override {
            cmds.emplace<PushTransformCmd>(PushTransformCmd{.transform = transform});
            cmds.emplace<DrawRectCmd>(DrawRectCmd{
                .position = {0.0f, 0.0f},
                .size = size_,
                .origin = {0.0f, 0.0f},
                .rotation = 0.0f,
                .color = fill_color_
            });
            cmds.emplace<PopTransformCmd>();
        }

    private:
        Vector2 size_{.x = 0.0f, .y = 0.0f};
    };

    class CircleShape : public Shape2D {
    public:
        ~CircleShape() override = default;

        CircleShape &set_radius(const float radius) {
            radius_ = radius;
            return *this;
        }

        [[nodiscard]] float get_radius() const {
            return radius_;
        }

    protected:
        void on_draw(RenderCommandList &cmds) override {
            cmds.emplace<PushTransformCmd>(PushTransformCmd{.transform = transform});
            cmds.emplace<DrawCircleCmd>(DrawCircleCmd{
                .center = {0.0f, 0.0f},
                .radius = radius_,
                .color = fill_color_
            });
            cmds.emplace<PopTransformCmd>();
        }

    private:
        float radius_{0.0f};
    };

    class TriangleShape : public Shape2D {
    public:
        ~TriangleShape() override = default;

        void set_points(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3) {
            p1_ = p1;
            p2_ = p2;
            p3_ = p3;
        }

        [[nodiscard]] std::array<Vector2, 3> get_points() const {
            return {p1_, p2_, p3_};
        }

        [[nodiscard]] Vector2 get_p1() const { return p1_; }
        [[nodiscard]] Vector2 get_p2() const { return p2_; }
        [[nodiscard]] Vector2 get_p3() const { return p3_; }

    protected:
        void on_draw(RenderCommandList &cmds) override {
            cmds.emplace<PushTransformCmd>(PushTransformCmd{.transform = transform});
            cmds.emplace<DrawTriangleCmd>(DrawTriangleCmd{
                .p1 = p1_,
                .p2 = p2_,
                .p3 = p3_,
                .color = fill_color_
            });
            cmds.emplace<PopTransformCmd>();
        }

    private:
        Vector2 p1_{.x = 0.0f, .y = 0.0f};
        Vector2 p2_{.x = 0.0f, .y = 0.0f};
        Vector2 p3_{.x = 0.0f, .y = 0.0f};
    };

    class PolygonShape : public Shape2D {
    public:
        ~PolygonShape() override = default;

        PolygonShape &set_points(std::vector<Vector2> points) {
            points_ = std::move(points);
            return *this;
        }

        [[nodiscard]] const std::vector<Vector2> &get_points() const {
            return points_;
        }

        PolygonShape &set_wireframe(const bool wireframe) {
            wireframe_ = wireframe;
            return *this;
        }

        [[nodiscard]] bool is_wireframe() const {
            return wireframe_;
        }

        PolygonShape &set_line_thickness(const float thickness) {
            line_thickness_ = thickness;
            return *this;
        }

        [[nodiscard]] float get_line_thickness() const {
            return line_thickness_;
        }

    protected:
        void on_draw(RenderCommandList &cmds) override {
            if (points_.size() < 3) return;
            cmds.emplace<PushTransformCmd>(PushTransformCmd{.transform = transform});
            cmds.emplace<DrawPolygonCmd>(DrawPolygonCmd{
                .points = points_,
                .color = fill_color_,
                .wireframe = wireframe_,
                .line_thickness = line_thickness_
            });
            cmds.emplace<PopTransformCmd>();
        }

    private:
        std::vector<Vector2> points_;
        bool wireframe_{false};
        float line_thickness_{1.0f};
    };
}
