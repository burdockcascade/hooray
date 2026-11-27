#pragma once

#include <algorithm>
#include <cmath>
#include <numbers>
#include "../core/math.hpp"
#include "node.hpp"

namespace hooray {
    class Camera2D : public Node {
    public:
        Camera2D &set_target(const float x, const float y) {
            target_ = {.x = x, .y = y};
            return *this;
        }

        [[nodiscard]] Vector2 get_target() const {
            return target_;
        }

        Camera2D &set_offset(const float x, const float y) {
            offset_ = {.x = x, .y = y};
            return *this;
        }

        [[nodiscard]] Vector2 get_offset() const {
            return offset_;
        }

        Camera2D &set_rotation(const float rotation) {
            rotation_ = rotation;
            return *this;
        }

        [[nodiscard]] float get_rotation() const {
            return rotation_;
        }

        Camera2D &set_zoom(const float zoom) {
            zoom_ = zoom;
            return *this;
        }

        [[nodiscard]] float get_zoom() const {
            return zoom_;
        }

        [[nodiscard]] Vector2 screen_to_world(Vector2 screen_pos) const {
            const float z = std::max(zoom_, 0.001f);
            const float dx = (screen_pos.x - offset_.x) / z;
            const float dy = (screen_pos.y - offset_.y) / z;

            if (rotation_ == 0.0f) {
                return {
                    .x = dx + target_.x,
                    .y = dy + target_.y
                };
            }

            // Inverse rotate by -_rotation (convert degrees to radians)
            constexpr float K_DEG_TO_RAD = std::numbers::pi / 180.0f;
            const float rad = -rotation_ * K_DEG_TO_RAD;
            const float cos_r = std::cos(rad);
            const float sin_r = std::sin(rad);

            return {
                .x = (dx * cos_r - dy * sin_r) + target_.x,
                .y = (dx * sin_r + dy * cos_r) + target_.y
            };
        }

    private:
        Vector2 target_{.x = 0.0f, .y = 0.0f};
        Vector2 offset_{.x = 0.0f, .y = 0.0f};
        float rotation_{0.0f};
        float zoom_{1.0f};
    };
}
