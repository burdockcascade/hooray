#include <raylib.h>
#include <rlgl.h>
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

        assetmanager_.load_all();

        for (auto& scene : scenes_) {
            scene.init(assetmanager_);
        }

        running_ = true;
        window_focused_ = ::IsWindowFocused();
        window_minimized_ = ::IsWindowMinimized();
        window_maximized_ = ::IsWindowMaximized();

        while (running_ && !::WindowShouldClose()) {
            const float dt = ::GetFrameTime();

            poll_and_dispatch_window_events();

            for (auto& scene : scenes_) {
                scene.update(dt);
            }

            ::BeginDrawing();
            ::ClearBackground(to_raylib_color(bg_color_));

            if (draw_fps_) {
                ::DrawFPS(10, 10);
            }

            render_commands_.clear();
            for (auto& scene : scenes_) {
                scene.draw(render_commands_);
            }

            execute_render_commands();

            ::EndDrawing();
        }

        for (auto& scene : scenes_) {
            scene.destroy();
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

    void App::execute_render_commands() const {
        const auto visitor = Overloaded{
            [](const BeginCamera2DCmd& cmd) {
                ::BeginMode2D(::Camera2D{
                    .offset = to_raylib_vector2(cmd.offset),
                    .target = to_raylib_vector2(cmd.target),
                    .rotation = cmd.rotation,
                    .zoom = cmd.zoom
                });
            },
            [](const EndCamera2DCmd&) {
                ::EndMode2D();
            },
            [](const PushTransformCmd& cmd) {
                ::rlPushMatrix();
                ::rlTranslatef(cmd.transform.position.x, cmd.transform.position.y, 0.0f);
                ::rlRotatef(cmd.transform.rotation, 0.0f, 0.0f, 1.0f);
                ::rlScalef(cmd.transform.scale.x, cmd.transform.scale.y, 1.0f);
            },
            [](const PopTransformCmd&) {
                ::rlPopMatrix();
            },
            [](const DrawTextureCmd& cmd) {
                if (cmd.texture.id == 0) return;
                ::DrawTexturePro(
                    to_raylib_texture(cmd.texture),
                    ::Rectangle{.x = cmd.source.x, .y = cmd.source.y, .width = cmd.source.width, .height = cmd.source.height},
                    ::Rectangle{.x = cmd.dest.x, .y = cmd.dest.y, .width = cmd.dest.width, .height = cmd.dest.height},
                    to_raylib_vector2(cmd.origin),
                    cmd.rotation,
                    to_raylib_color(cmd.tint)
                );
            },
            [](const DrawRectCmd& cmd) {
                ::DrawRectanglePro(
                    ::Rectangle{.x = cmd.position.x, .y = cmd.position.y, .width = cmd.size.x, .height = cmd.size.y},
                    to_raylib_vector2(cmd.origin),
                    cmd.rotation,
                    to_raylib_color(cmd.color)
                );
            },
            [](const DrawCircleCmd& cmd) {
                ::DrawCircleV(
                    to_raylib_vector2(cmd.center),
                    cmd.radius,
                    to_raylib_color(cmd.color)
                );
            },
            [](const DrawTriangleCmd& cmd) {
                ::DrawTriangle(
                    to_raylib_vector2(cmd.p1),
                    to_raylib_vector2(cmd.p2),
                    to_raylib_vector2(cmd.p3),
                    to_raylib_color(cmd.color)
                );
            },
            [](const DrawPolygonCmd& cmd) {
                if (cmd.points.size() < 3) return;
                const ::Color rl_color = to_raylib_color(cmd.color);

                if (cmd.wireframe) {
                    for (size_t i = 0; i < cmd.points.size(); ++i) {
                        const ::Vector2 p1 = to_raylib_vector2(cmd.points[i]);
                        const ::Vector2 p2 = to_raylib_vector2(cmd.points[(i + 1) % cmd.points.size()]);
                        ::DrawLineEx(p1, p2, cmd.line_thickness, rl_color);
                    }
                } else {
                    std::vector<::Vector2> rl_points;
                    rl_points.reserve(cmd.points.size());
                    for (const auto& pt : cmd.points) {
                        rl_points.push_back(to_raylib_vector2(pt));
                    }
                    ::DrawTriangleFan(rl_points.data(), static_cast<int>(rl_points.size()), rl_color);
                }
            }
        };

        for (const auto& cmd : render_commands_.commands()) {
            std::visit(visitor, cmd);
        }
    }

}