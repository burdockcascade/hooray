#include <raylib.h>
#include <hooray/core/app.hpp>
#include <hooray/platform/window.hpp>

#include "../raylibtools.hpp"

namespace hooray {

    namespace {
        template <class... Ts>
        struct Overloaded : Ts... {
            using Ts::operator()...;
        };
    }

    int App::run() {

        unsigned int backend_flags = 0;

        if (has_flag(window_flags_, WindowFlags::RESIZABLE))     backend_flags |= FLAG_WINDOW_RESIZABLE;
        if (has_flag(window_flags_, WindowFlags::FULLSCREEN))    backend_flags |= FLAG_FULLSCREEN_MODE;
        if (has_flag(window_flags_, WindowFlags::UNDECORATED))   backend_flags |= FLAG_WINDOW_UNDECORATED;
        if (has_flag(window_flags_, WindowFlags::VSYNC))         backend_flags |= FLAG_VSYNC_HINT;
        if (has_flag(window_flags_, WindowFlags::HIGH_DPI))      backend_flags |= FLAG_WINDOW_HIGHDPI;
        if (has_flag(window_flags_, WindowFlags::TRANSPARENT))   backend_flags |= FLAG_WINDOW_TRANSPARENT;
        if (has_flag(window_flags_, WindowFlags::ALWAYS_ON_TOP)) backend_flags |= FLAG_WINDOW_TOPMOST;
        if (has_flag(window_flags_, WindowFlags::HIDDEN))        backend_flags |= FLAG_WINDOW_HIDDEN;
        if (has_flag(window_flags_, WindowFlags::MAXIMIZED))     backend_flags |= FLAG_WINDOW_MAXIMIZED;
        if (has_flag(window_flags_, WindowFlags::MSAA_4X))       backend_flags |= FLAG_MSAA_4X_HINT;

        if (backend_flags != 0) {
            SetConfigFlags(backend_flags);
        }

        ::InitWindow(width_, height_, title_.c_str());
        ::SetTargetFPS(target_fps_);


        running_ = true;
        window_focused_ = ::IsWindowFocused();
        window_minimized_ = ::IsWindowMinimized();
        window_maximized_ = ::IsWindowMaximized();

        while (running_ && !::WindowShouldClose()) {
            const float dt = ::GetFrameTime();

            poll_and_dispatch_window_events();

            ::BeginDrawing();
            ::ClearBackground(to_raylib_color(bg_color_));

            if (draw_fps_) {
                ::DrawFPS(10, 10);
            }

            ::EndDrawing();
        }

        ::CloseWindow();
        return 0;
    }

    void App::poll_and_dispatch_window_events() {

        // Check Resize
        if (::IsWindowResized()) {
            width_ = ::GetScreenWidth();
            height_ = ::GetScreenHeight();
            for (auto& scene : scenes_) {
                scene.handle_window_event(WindowEvent{
                    .action = WindowAction::RESIZED,
                    .width = width_,
                    .height = height_
                });
            }
        }

        // Check Move
        const ::Vector2 pos = ::GetWindowPosition();
        if (pos.x != window_pos_.x || pos.y != window_pos_.y) {
            window_pos_ = Vector2{.x = pos.x, .y = pos.y};
            for (auto& scene : scenes_) {
                scene.handle_window_event(WindowEvent{
                    .action = WindowAction::MOVED,
                    .pos_x = static_cast<int>(pos.x),
                    .pos_y = static_cast<int>(pos.y)
                });
            }
        }

        // Check Focus
        const bool is_focused = ::IsWindowFocused();
        if (is_focused != window_focused_) {
            window_focused_ = is_focused;
            for (auto& scene : scenes_) {
                scene.handle_window_event(WindowEvent{
                    .action = is_focused ? WindowAction::FOCUS_GAINED : WindowAction::FOCUS_LOST
                });
            }
        }

        // Check Minimize / Restore
        const bool is_minimized = ::IsWindowMinimized();
        if (is_minimized != window_minimized_) {
            window_minimized_ = is_minimized;
            for (auto& scene : scenes_) {
                scene.handle_window_event(WindowEvent{
                    .action = is_minimized ? WindowAction::MINIMIZED : WindowAction::RESTORED
                });
            }
        }

        // Check Maximize / Unmaximize
        const bool is_maximized = ::IsWindowMaximized();
        if (is_maximized != window_maximized_) {
            window_maximized_ = is_maximized;
            for (auto& scene : scenes_) {
                scene.handle_window_event(WindowEvent{
                    .action = is_maximized ? WindowAction::MAXIMIZED : WindowAction::UNMAXIMIZED,
                    .width = width_,
                    .height = height_
                });
            }
        }
    }

}