#include <variant>
#include <raylib.h>
#include "application.hpp"

#include <functional>

#include "commands.hpp"
#include "conversion.hpp"

namespace Hooray {

    namespace {
        template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
        template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    }

    void Application::execute_commands() const {
        for (const auto& cmd : command_queue_) {
            std::visit(overloaded{
                [](const ClearBackgroundCmd& arg) {
                    ::ClearBackground(ToRay(arg.color));
                },
                [](const BeginMode2DCmd& arg) {
                    ::BeginMode2D(ToRay(arg.camera));
                },
                [](const EndMode2DCmd&) {
                    ::EndMode2D();
                },
                [](const DrawFPSCmd& arg) {
                    ::DrawFPS(static_cast<int>(arg.position.x), static_cast<int>(arg.position.y));
                },
                [](const DrawPixelCmd& arg) {
                    ::DrawPixelV(ToRay(arg.position), ToRay(arg.color));
                },
                [](const DrawLineCmd& arg) {
                    ::DrawLineEx(ToRay(arg.start), ToRay(arg.end), arg.thickness, ToRay(arg.color));
                },
                [](const DrawCircleCmd& arg) {
                    ::DrawCircleV(ToRay(arg.center), arg.radius, ToRay(arg.color));
                },
                [](const DrawRectangleCmd& arg) {
                    ::DrawRectangleRec(ToRay(arg.rect), ToRay(arg.color));
                },
                [](const DrawTriangleCmd& arg) {
                    ::DrawTriangle(ToRay(arg.p1), ToRay(arg.p2), ToRay(arg.p3), ToRay(arg.color));
                },
                [](const DrawEllipseCmd& arg) {
                    ::DrawEllipseV(ToRay(arg.center), arg.radius_h, arg.radius_v, ToRay(arg.color));
                },
                [](const DrawTextCmd& arg) {
                    const Font font = arg.font_face.id ? ToRay(arg.font_face) : ::GetFontDefault();
                    ::DrawTextEx(font, arg.text.c_str(), ToRay(arg.position), arg.font_size, arg.spacing, ToRay(arg.color));
                },
                [](const DrawTextureCmd& arg) {
                    ::DrawTextureV(ToRay(arg.texture), ToRay(arg.position), ToRay(arg.tint));
                },
                [](const DrawTextureRecCmd& arg) {
                    ::DrawTextureRec(ToRay(arg.texture), ToRay(arg.source), ToRay(arg.position), ToRay(arg.tint));
                },
                [](const DrawTextureProCmd& arg) {
                    ::DrawTexturePro(ToRay(arg.texture), ToRay(arg.source), ToRay(arg.dest), ToRay(arg.origin), arg.rotation, ToRay(arg.tint));
                },
                [](const DrawPolyCmd& arg) {
                    ::DrawPoly(ToRay(arg.center), arg.sides, arg.radius, arg.rotation, ToRay(arg.color));
                },
                [](const PlaySoundCmd& arg) {
                    ::PlaySound(ToRay(arg.sound));
                },
                [](const StopSoundCmd& arg) {
                    ::StopSound(ToRay(arg.sound));
                },
                [](const PauseSoundCmd& arg) {
                    ::PauseSound(ToRay(arg.sound));
                },
                [](const ResumeSoundCmd& arg) {
                    ::ResumeSound(ToRay(arg.sound));
                },
                [](const SetSoundVolumeCmd& arg) {
                    ::SetSoundVolume(ToRay(arg.sound), arg.volume);
                },
                [](const SetSoundPitchCmd& arg) {
                    ::SetSoundPitch(ToRay(arg.sound), arg.pitch);
                },
                [](const PlayMusicStreamCmd& arg) {
                    ::PlayMusicStream(ToRay(arg.music));
                },
                [](const UpdateMusicStreamCmd& arg) {
                    ::UpdateMusicStream(ToRay(arg.music));
                },
                [](const StopMusicStreamCmd& arg) {
                    ::StopMusicStream(ToRay(arg.music));
                },
                [](const PauseMusicStreamCmd& arg) {
                    ::PauseMusicStream(ToRay(arg.music));
                },
                [](const ResumeMusicStreamCmd& arg) {
                    ::ResumeMusicStream(ToRay(arg.music));
                },
                [](const SetMusicVolumeCmd& arg) {
                    ::SetMusicVolume(ToRay(arg.music), arg.volume);
                }
            }, cmd);
        }
    }

    void Renderer::clearBackground(Color color) const {
        command_queue_.emplace_back(ClearBackgroundCmd{color});
    }

    void Renderer::add_command(Command command) const {
        command_queue_.emplace_back(std::move(command));
    }

    void Renderer::add_commands(std::vector<Command> commands) const {
        command_queue_.insert(command_queue_.end(), std::make_move_iterator(commands.begin()), std::make_move_iterator(commands.end()));
    }

    void Renderer::clear_commands() const {
        command_queue_.clear();
    }

    void Layer2d::drawLine(const Vector2 start, const Vector2 end, const float thickness, const Color color) const {
        command_queue_.emplace_back(DrawLineCmd{.start = start, .end = end, .thickness = thickness, .color = color});
    }

    void Layer2d::drawCircle(const Vector2 center, const float radius, const Color color) const {
        command_queue_.emplace_back(DrawCircleCmd{.center = center, .radius = radius, .color = color});
    }

    void Layer2d::drawRectangle(const Rectangle rect, const Color color) const {
        command_queue_.emplace_back(DrawRectangleCmd{.rect = rect, .color = color});
    }

    void Layer2d::drawText(std::string text, const Vector2 pos) const {
        command_queue_.emplace_back(DrawTextCmd{
            .text = std::move(text),
            .position = pos,
            .font_size = 20.0f,
            .spacing = 1.0f,
            .color = Palette::White
        });
    }

    void Application::run() {

        command_queue_.reserve(1024);

        InitWindow(width_, height_, title_.c_str());
        InitAudioDevice();
        SetTargetFPS(60);

        on_init();

        auto render = Renderer{command_queue_};

        while (!WindowShouldClose()) {

            const float delta_time = GetFrameTime();

            // Keyboard Events
            int key = GetKeyPressed();
            while (key > 0) {
                on_key_pressed(key);
                key = GetKeyPressed();
            }

            // Mouse Press & Release Events
            const Vector2 mouse_pos = FromRay(::GetMousePosition());
            for (int button = MOUSE_BUTTON_LEFT; button <= MOUSE_BUTTON_BACK; ++button) {
                if (IsMouseButtonPressed(button)) {
                    on_mouse_pressed(button, mouse_pos);
                }
                if (IsMouseButtonReleased(button)) {
                    on_mouse_released(button, mouse_pos);
                }
            }

            // Mouse Movement Events
            const Vector2 delta = FromRay(::GetMouseDelta());
            if (delta.x != 0.0f || delta.y != 0.0f) {
                on_mouse_moved(mouse_pos);
            }

            // Update
            on_update(delta_time);

            // Draw
            BeginDrawing();
            on_draw(render);
            execute_commands();
            EndDrawing();

            command_queue_.clear();
        }

        if (IsAudioDeviceReady()) {
            CloseAudioDevice();
        }

        if (IsWindowReady()) {
            CloseWindow();
        }

    }


}
