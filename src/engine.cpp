#include "engine.hpp"
#include <ranges>
#include <variant>
#include "raylib.h"

namespace Hooray {

    namespace {
        template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
        template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    }

    // ==========================================
    // LifecycleManager Implementation
    // ==========================================

    void LifecycleManager::add_listener(const std::shared_ptr<LifecycleListener>& listener) {
        listeners_.push_back(listener);
    }

    void LifecycleManager::remove_listener(const std::shared_ptr<LifecycleListener>& listener) {
        std::erase(listeners_, listener);
    }

    void LifecycleManager::notify_init() const {
        for (const auto& listener : listeners_) {
            listener->on_init();
        }
    }

    void LifecycleManager::notify_update(const float delta_time) const {
        for (const auto& listener : listeners_) {
            listener->on_update(delta_time);
        }
    }

    void LifecycleManager::notify_draw() const {
        for (const auto& listener : listeners_) {
            listener->on_draw();
        }
    }

    // ==========================================
    // InputManager Implementation
    // ==========================================

    void InputManager::add_listener(const std::shared_ptr<InputListener>& listener) {
        listeners_.push_back(listener);
    }

    void InputManager::remove_listener(const std::shared_ptr<InputListener>& listener) {
        std::erase(listeners_, listener);
    }

    bool InputManager::is_key_down(const int key) {
        return IsKeyDown(key);
    }

    bool InputManager::is_mouse_button_down(const int button) {
        return IsMouseButtonDown(button);
    }

    Vector2 InputManager::get_mouse_position() {
        return GetMousePosition();
    }

    Vector2 InputManager::get_mouse_delta() {
        return GetMouseDelta();
    }

    void InputManager::notify_key_pressed(const int key) {
        for (const auto& listener : std::views::reverse(listeners_)) {
            if (listener->on_key_pressed(key)) break;
        }
    }

    void InputManager::notify_mouse_pressed(const int button, const Vector2 pos) {
        for (const auto& listener : std::views::reverse(listeners_)) {
            if (listener->on_mouse_pressed(button, pos)) break;
        }
    }

    void InputManager::notify_mouse_released(const int button, const Vector2 pos) {
        for (const auto& listener : std::views::reverse(listeners_)) {
            if (listener->on_mouse_released(button, pos)) break;
        }
    }

    void InputManager::notify_mouse_moved(const Vector2 pos) {
        for (const auto& listener : std::views::reverse(listeners_)) {
            if (listener->on_mouse_moved(pos)) break;
        }
    }

    // ==========================================
    // Engine Implementation
    // ==========================================

    Engine::Engine(const int width, const int height, std::string title)
        : width_(width), height_(height), title_(std::move(title)) {}

    Engine::~Engine() = default;

    void Engine::run() {
        run_loop(true);
    }

    void Engine::display() {
        run_loop(false);
    }

    void Engine::run_loop(const bool clear_buffer_after_frame) {
        InitWindow(width_, height_, title_.c_str());
        InitAudioDevice();
        SetTargetFPS(60);

        lifecycle_manager_.notify_init();

        while (!WindowShouldClose()) {
            if (clear_buffer_after_frame) command_buffer_.clear();

            const float delta_time = GetFrameTime();

            // Keyboard Events
            int key = GetKeyPressed();
            while (key > 0) {
                input_manager_.notify_key_pressed(key);
                key = GetKeyPressed();
            }

            // Mouse Press & Release Events
            const Vector2 mouse_pos = GetMousePosition();
            for (int button = MOUSE_BUTTON_LEFT; button <= MOUSE_BUTTON_BACK; ++button) {
                if (IsMouseButtonPressed(button)) {
                    input_manager_.notify_mouse_pressed(button, mouse_pos);
                }
                if (IsMouseButtonReleased(button)) {
                    input_manager_.notify_mouse_released(button, mouse_pos);
                }
            }

            // Mouse Movement Events
            const Vector2 delta = GetMouseDelta();
            if (delta.x != 0.0f || delta.y != 0.0f) {
               input_manager_.notify_mouse_moved(mouse_pos);
            }

            // Update
            lifecycle_manager_.notify_update(delta_time);

            // Draw
            BeginDrawing();
            lifecycle_manager_.notify_draw();
            execute_commands();

            EndDrawing();
        }

        if (IsAudioDeviceReady()) {
            CloseAudioDevice();
        }
        if (IsWindowReady()) {
            CloseWindow();
        }
    }

    void Engine::execute_commands() const {
        for (const auto& cmd : command_buffer_.get_commands()) {
            std::visit(overloaded{
                [](const ClearBackgroundCmd& arg) {
                    ::ClearBackground(arg.color);
                },
                [](const BeginMode2DCmd& arg) {
                    ::BeginMode2D(arg.camera);
                },
                [](const EndMode2DCmd&) {
                    ::EndMode2D();
                },
                [](const DrawFPSCmd& arg) {
                    ::DrawFPS(static_cast<int>(arg.position.x), static_cast<int>(arg.position.y));
                },
                [](const DrawPixelCmd& arg) {
                    ::DrawPixelV(arg.position, arg.color);
                },
                [](const DrawLineCmd& arg) {
                    ::DrawLineEx(arg.start, arg.end, arg.thickness, arg.color);
                },
                [](const DrawCircleCmd& arg) {
                    ::DrawCircleV(arg.center, arg.radius, arg.color);
                },
                [](const DrawRectangleCmd& arg) {
                    ::DrawRectangleRec(arg.rect, arg.color);
                },
                [](const DrawTriangleCmd& arg) {
                    ::DrawTriangle(arg.p1, arg.p2, arg.p3, arg.color);
                },
                [](const DrawEllipseCmd& arg) {
                    ::DrawEllipseV(arg.center, arg.radius_h, arg.radius_v, arg.color);
                },
                [](const DrawTextCmd& arg) {
                    ::DrawTextEx(arg.font_face, arg.text.c_str(), arg.position, arg.font_size, arg.spacing, arg.color);
                },
                [](const DrawTextureCmd& arg) {
                    ::DrawTextureV(arg.texture, arg.position, arg.tint);
                },
                [](const DrawTextureRecCmd& arg) {
                    ::DrawTextureRec(arg.texture, arg.source, arg.position, arg.tint);
                },
                [](const DrawTextureProCmd& arg) {
                    ::DrawTexturePro(arg.texture, arg.source, arg.dest, arg.origin, arg.rotation, arg.tint);
                },
                [](const DrawPolyCmd& arg) {
                    ::DrawPoly(arg.center, arg.sides, arg.radius, arg.rotation, arg.color);
                },
                [](const PlaySoundCmd& arg) {
                    ::PlaySound(arg.sound);
                },
                [](const StopSoundCmd& arg) {
                    ::StopSound(arg.sound);
                },
                [](const PauseSoundCmd& arg) {
                    ::PauseSound(arg.sound);
                },
                [](const ResumeSoundCmd& arg) {
                    ::ResumeSound(arg.sound);
                },
                [](const SetSoundVolumeCmd& arg) {
                    ::SetSoundVolume(arg.sound, arg.volume);
                },
                [](const SetSoundPitchCmd& arg) {
                    ::SetSoundPitch(arg.sound, arg.pitch);
                },
                [](const PlayMusicStreamCmd& arg) {
                    ::PlayMusicStream(arg.music);
                },
                [](const UpdateMusicStreamCmd& arg) {
                    ::UpdateMusicStream(arg.music);
                },
                [](const StopMusicStreamCmd& arg) {
                    ::StopMusicStream(arg.music);
                },
                [](const PauseMusicStreamCmd& arg) {
                    ::PauseMusicStream(arg.music);
                },
                [](const ResumeMusicStreamCmd& arg) {
                    ::ResumeMusicStream(arg.music);
                },
                [](const SetMusicVolumeCmd& arg) {
                    ::SetMusicVolume(arg.music, arg.volume);
                }
            }, cmd);
        }
    }

}