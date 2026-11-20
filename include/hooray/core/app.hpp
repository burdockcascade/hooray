#pragma once
#include <string>
#include <utility>
#include <vector>

#include "color.hpp"
#include "math.hpp"
#include "hooray/platform/window.hpp"
#include "hooray/scenegraph/scene.hpp"

namespace hooray {

    class App {
    public:
        void set_title(std::string title) {
            title_ = std::move(title);
        }

        void set_fps_target(const int fps) noexcept {
            target_fps_ = fps;
        }

        void draw_fps(const bool draw) noexcept {
            draw_fps_ = draw;
        }

        void set_window_size(const int width, const int height) noexcept {
            width_ = width;
            height_ = height;
        }

        void set_background_color(const int r, const int g, const int b, const int a) noexcept {
            bg_color_ = Color{
                .r = static_cast<uint8_t>(r),
                .g = static_cast<uint8_t>(g),
                .b = static_cast<uint8_t>(b),
                .a = static_cast<uint8_t>(a)
            };
        }

        void set_background_color(const Color& color) noexcept {
            bg_color_ = color;
        }

        // Enable a specific flag without overwriting existing ones
        void enable_window_flag(const WindowFlags flag) noexcept {
            window_flags_ |= flag;
        }

        // Disable a specific flag
        void disable_window_flag(const WindowFlags flag) noexcept {
            window_flags_ = static_cast<WindowFlags>(
                static_cast<uint32_t>(window_flags_) & ~static_cast<uint32_t>(flag)
            );
        }

        // Convenience shorthand for common flags
        void set_resizable(const bool resizable = true) noexcept {
            resizable ? enable_window_flag(WindowFlags::RESIZABLE)
                      : disable_window_flag(WindowFlags::RESIZABLE);
        }

        void add_scene(Scene scene) {
            scenes_.push_back(std::move(scene));
        }

        int run();

        void poll_and_dispatch_window_events();

    private:
        std::string title_ = "Hooray Application";
        int width_ = 800;
        int height_ = 600;
        int target_fps_ = 60;
        bool draw_fps_ = false;
        Color bg_color_{colors::WHITE};
        WindowFlags window_flags_{WindowFlags::NONE};

        bool running_ = false;
        bool window_focused_ = true;
        bool window_minimized_ = false;
        bool window_maximized_ = false;
        Vector2 window_pos_{0, 0};

        std::vector<Scene> scenes_;

    };

}
