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

}