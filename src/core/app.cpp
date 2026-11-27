#include <raylib.h>
#include <rlgl.h>
#include <utility>
#include <array>
#include "hooray/core/app.hpp"
#include "hooray/platform/input.hpp"
#include "../raylibtools.hpp"
#include "hooray/assets/assetmanager.hpp"

namespace hooray {

    namespace {

        template <class... Ts>
        struct Overloaded : Ts... {
            using Ts::operator()...;
        };

        struct KeyMapping {
            Key key;
            int raylib_key;
        };

        constexpr KeyMapping KEY_MAPPINGS[] = {
            {Key::SPACE, KEY_SPACE}, {Key::APOSTROPHE, KEY_APOSTROPHE},
            {Key::COMMA, KEY_COMMA}, {Key::MINUS, KEY_MINUS},
            {Key::PERIOD, KEY_PERIOD}, {Key::SLASH, KEY_SLASH},
            {Key::ZERO, KEY_ZERO}, {Key::ONE, KEY_ONE}, {Key::TWO, KEY_TWO},
            {Key::THREE, KEY_THREE}, {Key::FOUR, KEY_FOUR}, {Key::FIVE, KEY_FIVE},
            {Key::SIX, KEY_SIX}, {Key::SEVEN, KEY_SEVEN}, {Key::EIGHT, KEY_EIGHT},
            {Key::NINE, KEY_NINE}, {Key::SEMICOLON, KEY_SEMICOLON},
            {Key::EQUAL, KEY_EQUAL},
            {Key::A, KEY_A}, {Key::B, KEY_B}, {Key::C, KEY_C}, {Key::D, KEY_D},
            {Key::E, KEY_E}, {Key::F, KEY_F}, {Key::G, KEY_G}, {Key::H, KEY_H},
            {Key::I, KEY_I}, {Key::J, KEY_J}, {Key::K, KEY_K}, {Key::L, KEY_L},
            {Key::M, KEY_M}, {Key::N, KEY_N}, {Key::O, KEY_O}, {Key::P, KEY_P},
            {Key::Q, KEY_Q}, {Key::R, KEY_R}, {Key::S, KEY_S}, {Key::T, KEY_T},
            {Key::U, KEY_U}, {Key::V, KEY_V}, {Key::W, KEY_W}, {Key::X, KEY_X},
            {Key::Y, KEY_Y}, {Key::Z, KEY_Z},
            {Key::LEFT_BRACKET, KEY_LEFT_BRACKET}, {Key::BACKSLASH, KEY_BACKSLASH},
            {Key::RIGHT_BRACKET, KEY_RIGHT_BRACKET}, {Key::GRAVE, KEY_GRAVE},
            {Key::ESCAPE, KEY_ESCAPE}, {Key::ENTER, KEY_ENTER}, {Key::TAB, KEY_TAB},
            {Key::BACKSPACE, KEY_BACKSPACE}, {Key::INSERT, KEY_INSERT},
            {Key::DELETE, KEY_DELETE}, {Key::RIGHT, KEY_RIGHT}, {Key::LEFT, KEY_LEFT},
            {Key::DOWN, KEY_DOWN}, {Key::UP, KEY_UP}, {Key::PAGEUP, KEY_PAGE_UP},
            {Key::PAGEDOWN, KEY_PAGE_DOWN}, {Key::HOME, KEY_HOME}, {Key::END, KEY_END},
            {Key::CAPSLOCK, KEY_CAPS_LOCK}, {Key::SCROLL_LOCK, KEY_SCROLL_LOCK},
            {Key::NUM_LOCK, KEY_NUM_LOCK}, {Key::PRINT_SCREEN, KEY_PRINT_SCREEN},
            {Key::PAUSE, KEY_PAUSE},
            {Key::F1, KEY_F1}, {Key::F2, KEY_F2}, {Key::F3, KEY_F3}, {Key::F4, KEY_F4},
            {Key::F5, KEY_F5}, {Key::F6, KEY_F6}, {Key::F7, KEY_F7}, {Key::F8, KEY_F8},
            {Key::F9, KEY_F9}, {Key::F10, KEY_F10}, {Key::F11, KEY_F11}, {Key::F12, KEY_F12},
            {Key::KP0, KEY_KP_0}, {Key::KP1, KEY_KP_1}, {Key::KP2, KEY_KP_2},
            {Key::KP3, KEY_KP_3}, {Key::KP4, KEY_KP_4}, {Key::KP5, KEY_KP_5},
            {Key::KP6, KEY_KP_6}, {Key::KP7, KEY_KP_7}, {Key::KP8, KEY_KP_8},
            {Key::KP9, KEY_KP_9}, {Key::KP_DECIMAL, KEY_KP_DECIMAL},
            {Key::KP_DIVIDE, KEY_KP_DIVIDE}, {Key::KP_MULTIPLY, KEY_KP_MULTIPLY},
            {Key::KP_SUBTRACT, KEY_KP_SUBTRACT}, {Key::KP_ADD, KEY_KP_ADD},
            {Key::KP_ENTER, KEY_KP_ENTER}, {Key::KP_EQUAL, KEY_KP_EQUAL},
            {Key::LEFTSHIFT, KEY_LEFT_SHIFT}, {Key::LEFT_CONTROL, KEY_LEFT_CONTROL},
            {Key::LEFT_ALT, KEY_LEFT_ALT}, {Key::LEFT_SUPER, KEY_LEFT_SUPER},
            {Key::RIGHTSHIFT, KEY_RIGHT_SHIFT}, {Key::RIGHT_CONTROL, KEY_RIGHT_CONTROL},
            {Key::RIGHT_ALT, KEY_RIGHT_ALT}, {Key::RIGHT_SUPER, KEY_RIGHT_SUPER},
            {Key::MENU, KEY_KB_MENU}
        };

        constexpr std::pair<MouseButton, int> MOUSE_MAPPINGS[] = {
            {MouseButton::LEFT, MOUSE_BUTTON_LEFT},
            {MouseButton::RIGHT, MOUSE_BUTTON_RIGHT},
            {MouseButton::MIDDLE, MOUSE_BUTTON_MIDDLE},
            {MouseButton::SIDE, MOUSE_BUTTON_SIDE},
            {MouseButton::EXTRA, MOUSE_BUTTON_EXTRA},
            {MouseButton::FORWARD, MOUSE_BUTTON_FORWARD},
            {MouseButton::BACK, MOUSE_BUTTON_BACK}
        };

        constexpr std::pair<GamepadButton, int> GAMEPAD_BUTTON_MAPPINGS[] = {
            {GamepadButton::DPAD_UP,      GAMEPAD_BUTTON_LEFT_FACE_UP},
            {GamepadButton::DPAD_RIGHT,   GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
            {GamepadButton::DPAD_DOWN,    GAMEPAD_BUTTON_LEFT_FACE_DOWN},
            {GamepadButton::DPAD_LEFT,    GAMEPAD_BUTTON_LEFT_FACE_LEFT},
            {GamepadButton::FACE_UP,      GAMEPAD_BUTTON_RIGHT_FACE_UP},
            {GamepadButton::FACE_RIGHT,   GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
            {GamepadButton::FACE_DOWN,    GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
            {GamepadButton::FACE_LEFT,    GAMEPAD_BUTTON_RIGHT_FACE_LEFT},
            {GamepadButton::LEFT_BUMPER,  GAMEPAD_BUTTON_LEFT_TRIGGER_1},
            {GamepadButton::LEFT_TRIGGER, GAMEPAD_BUTTON_LEFT_TRIGGER_2},
            {GamepadButton::RIGHT_BUMPER, GAMEPAD_BUTTON_RIGHT_TRIGGER_1},
            {GamepadButton::RIGHT_TRIGGER,GAMEPAD_BUTTON_RIGHT_TRIGGER_2},
            {GamepadButton::MIDDLE_LEFT,  GAMEPAD_BUTTON_MIDDLE_LEFT},
            {GamepadButton::MIDDLE,       GAMEPAD_BUTTON_MIDDLE},
            {GamepadButton::MIDDLE_RIGHT, GAMEPAD_BUTTON_MIDDLE_RIGHT},
            {GamepadButton::LEFT_THUMB,   GAMEPAD_BUTTON_LEFT_THUMB},
            {GamepadButton::RIGHT_THUMB,  GAMEPAD_BUTTON_RIGHT_THUMB}
        };

        constexpr std::pair<GamepadAxis, int> GAMEPAD_AXIS_MAPPINGS[] = {
            {GamepadAxis::LEFT_X,        GAMEPAD_AXIS_LEFT_X},
            {GamepadAxis::LEFT_Y,        GAMEPAD_AXIS_LEFT_Y},
            {GamepadAxis::RIGHT_X,       GAMEPAD_AXIS_RIGHT_X},
            {GamepadAxis::RIGHT_Y,       GAMEPAD_AXIS_RIGHT_Y},
            {GamepadAxis::LEFT_TRIGGER,  GAMEPAD_AXIS_LEFT_TRIGGER},
            {GamepadAxis::RIGHT_TRIGGER, GAMEPAD_AXIS_RIGHT_TRIGGER}
        };

        constexpr int MAX_GAMEPADS = 4;
        constexpr int NUM_AXES = 6;
        constexpr float AXIS_DEAD_ZONE = 0.05f;

        struct GamepadStateTracker {
            std::array<bool, MAX_GAMEPADS> connected{};
            std::array<std::array<float, NUM_AXES>, MAX_GAMEPADS> prev_axes{};
        };

        GamepadStateTracker g_gamepad_state{};

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
            poll_and_dispatch_mouse_input();
            poll_and_dispatch_kb_input();
            poll_and_dispatch_gamepad_input();

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

        assetmanager_.unload_all();
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

    void App::poll_and_dispatch_kb_input() {
        auto dispatch_key = [&](const KeyEvent& ev) {
            for (auto& scene : scenes_) {
                scene.handle_key_event(ev);
            }
        };

        for (const auto& mapping : KEY_MAPPINGS) {
            if (::IsKeyPressed(mapping.raylib_key)) {
                dispatch_key(KeyEvent{.key = mapping.key, .action = KeyAction::PRESSED});
            } else if (::IsKeyDown(mapping.raylib_key)) {
                dispatch_key(KeyEvent{.key = mapping.key, .action = KeyAction::DOWN});
            } else if (::IsKeyReleased(mapping.raylib_key)) {
                dispatch_key(KeyEvent{.key = mapping.key, .action = KeyAction::RELEASED});
            }
        }
    }

    void App::poll_and_dispatch_mouse_input() {

        auto dispatch_mouse = [&](const MouseEvent& ev) {
            for (auto& scene : scenes_) {
                scene.handle_mouse_event(ev);
            }
        };

        const ::Vector2 rl_pos = ::GetMousePosition();
        const ::Vector2 rl_delta = ::GetMouseDelta();
        const ::Vector2 rl_wheel = ::GetMouseWheelMoveV();

        const Vector2 pos{.x = rl_pos.x, .y = rl_pos.y};
        const Vector2 delta{.x = rl_delta.x, .y = rl_delta.y};
        const Vector2 scroll{.x = rl_wheel.x, .y = rl_wheel.y};

        // Mouse Buttons (Pressed / Down / Released)
        for (const auto& [btn, rl_btn] : MOUSE_MAPPINGS) {
            if (::IsMouseButtonPressed(rl_btn)) {
                dispatch_mouse(MouseEvent{
                    .action = MouseAction::PRESSED,
                    .button = btn,
                    .position = pos,
                    .delta = delta,
                    .scroll = scroll
                });
            } else if (::IsMouseButtonDown(rl_btn)) {
                dispatch_mouse(MouseEvent{
                    .action = MouseAction::DOWN,
                    .button = btn,
                    .position = pos,
                    .delta = delta,
                    .scroll = scroll
                });
            } else if (::IsMouseButtonReleased(rl_btn)) {
                dispatch_mouse(MouseEvent{
                    .action = MouseAction::RELEASED,
                    .button = btn,
                    .position = pos,
                    .delta = delta,
                    .scroll = scroll
                });
            }
        }

        // Mouse Movement
        if (delta.x != 0.0f || delta.y != 0.0f) {
            dispatch_mouse(MouseEvent{
                .action = MouseAction::MOVED,
                .button = MouseButton::NONE,
                .position = pos,
                .delta = delta,
                .scroll = scroll
            });
        }

        // Mouse Wheel Scroll
        if (scroll.x != 0.0f || scroll.y != 0.0f) {
            dispatch_mouse(MouseEvent{
                .action = MouseAction::SCROLLED,
                .button = MouseButton::NONE,
                .position = pos,
                .delta = delta,
                .scroll = scroll
            });
        }
    }

    void App::poll_and_dispatch_gamepad_input() {

        auto dispatch_gamepad = [&](const GamepadEvent& ev) {
            for (auto& scene : scenes_) {
                scene.handle_gamepad_event(ev);
            }
        };

        // Poll Gamepad State
        for (int pad = 0; pad < MAX_GAMEPADS; ++pad) {
            const bool is_avail = ::IsGamepadAvailable(pad);
            const bool was_avail = g_gamepad_state.connected[pad];

            if (is_avail && !was_avail) {
                g_gamepad_state.connected[pad] = true;
                dispatch_gamepad(GamepadEvent{
                    .gamepad_id = pad,
                    .action = GamepadAction::CONNECTED
                });
            } else if (!is_avail && was_avail) {
                g_gamepad_state.connected[pad] = false;
                g_gamepad_state.prev_axes[pad].fill(0.0f);
                dispatch_gamepad(GamepadEvent{
                    .gamepad_id = pad,
                    .action = GamepadAction::DISCONNECTED
                });
            }

            if (!is_avail) continue;

            // Gamepad Buttons (Pressed / Down / Released)
            for (const auto& [btn, rl_btn] : GAMEPAD_BUTTON_MAPPINGS) {
                if (::IsGamepadButtonPressed(pad, rl_btn)) {
                    dispatch_gamepad(GamepadEvent{
                        .gamepad_id = pad,
                        .action = GamepadAction::PRESSED,
                        .button = btn
                    });
                } else if (::IsGamepadButtonDown(pad, rl_btn)) {
                    dispatch_gamepad(GamepadEvent{
                        .gamepad_id = pad,
                        .action = GamepadAction::DOWN,
                        .button = btn
                    });
                } else if (::IsGamepadButtonReleased(pad, rl_btn)) {
                    dispatch_gamepad(GamepadEvent{
                        .gamepad_id = pad,
                        .action = GamepadAction::RELEASED,
                        .button = btn
                    });
                }
            }

            // Gamepad Axes
            const int axis_count = ::GetGamepadAxisCount(pad);
            for (size_t i = 0; i < std::size(GAMEPAD_AXIS_MAPPINGS); ++i) {
                const auto [axis, rl_axis] = GAMEPAD_AXIS_MAPPINGS[i];
                if (rl_axis >= axis_count) continue;

                float raw_val = ::GetGamepadAxisMovement(pad, rl_axis);
                if (std::abs(raw_val) < AXIS_DEAD_ZONE) {
                    raw_val = 0.0f;
                }

                const float prev_val = g_gamepad_state.prev_axes[pad][i];
                const float delta = raw_val - prev_val;
                g_gamepad_state.prev_axes[pad][i] = raw_val;

                // Dispatch if stick/trigger is actively tilted or just returned to zero
                if (raw_val != 0.0f || delta != 0.0f) {
                    dispatch_gamepad(GamepadEvent{
                        .gamepad_id = pad,
                        .action = GamepadAction::AXIS_MOVED,
                        .button = GamepadButton::UNKNOWN,
                        .axis = axis,
                        .axis_value = raw_val,
                        .axis_delta = delta
                    });
                }
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