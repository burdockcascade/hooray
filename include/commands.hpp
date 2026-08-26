#pragma once

#include <vector>
#include <variant>
#include <type_traits>
#include <string>
#include <raylib.h>

namespace Hooray {

    // ==========================================
    // State Commands
    // ==========================================

    struct ClearBackgroundCmd {
        Color color{ RAYWHITE };
    };

    struct BeginMode2DCmd {
        Camera2D camera;
    };

    struct EndMode2DCmd {};

    // ==========================================
    // Primitive Draw Commands
    // ==========================================

    struct DrawFPSCmd {
        Vector2 position;
    };

    struct DrawPixelCmd {
        Vector2 position;
        Color color;
    };

    struct DrawLineCmd {
        Vector2 start;
        Vector2 end;
        float thickness{ 1.0f };
        Color color;
    };

    struct DrawCircleCmd {
        Vector2 center;
        float radius;
        Color color;
    };

    struct DrawRectangleCmd {
        Rectangle rect;
        Color color;
    };

    struct DrawTriangleCmd {
        Vector2 p1;
        Vector2 p2;
        Vector2 p3;
        Color color;
    };

    struct DrawEllipseCmd {
        Vector2 center;
        float radius_h;
        float radius_v;
        Color color;
    };

    struct DrawTextCmd {
        std::string text;
        Vector2 position;
        Font font_face;
        float font_size;
        float spacing;
        Color color;
    };

    struct DrawTextureCmd {
        Texture2D texture;
        Vector2 position;
        Color tint;
    };

    struct DrawTextureRecCmd {
        Texture2D texture;
        Rectangle source;
        Vector2 position;
        Color tint;
    };

    struct DrawTextureProCmd {
        Texture2D texture;
        Rectangle source;
        Rectangle dest;
        Vector2 origin;
        float rotation;
        Color tint;
    };

    struct DrawPolyCmd {
        Vector2 center;
        int sides;
        float radius;
        float rotation;
        Color color;
    };

    // ==========================================
    // Audio Commands
    // ==========================================

    struct PlaySoundCmd {
        Sound sound;
    };

    struct StopSoundCmd {
        Sound sound;
    };

    struct PauseSoundCmd {
        Sound sound;
    };

    struct ResumeSoundCmd {
        Sound sound;
    };

    struct SetSoundVolumeCmd {
        Sound sound;
        float volume;
    };

    struct SetSoundPitchCmd {
        Sound sound;
        float pitch;
    };

    struct PlayMusicStreamCmd {
        Music music;
    };

    struct UpdateMusicStreamCmd {
        Music music;
    };

    struct StopMusicStreamCmd {
        Music music;
    };

    struct PauseMusicStreamCmd {
        Music music;
    };

    struct ResumeMusicStreamCmd {
        Music music;
    };

    struct SetMusicVolumeCmd {
        Music music;
        float volume;
    };

    // ==========================================
    // Command Variant & Queue
    // ==========================================

    using Command = std::variant<
        ClearBackgroundCmd,
        BeginMode2DCmd,
        EndMode2DCmd,
        DrawFPSCmd,
        DrawPixelCmd,
        DrawLineCmd,
        DrawCircleCmd,
        DrawRectangleCmd,
        DrawTriangleCmd,
        DrawEllipseCmd,
        DrawTextCmd,
        DrawTextureCmd,
        DrawTextureRecCmd,
        DrawTextureProCmd,
        DrawPolyCmd,
        // Audio
        PlaySoundCmd,
        StopSoundCmd,
        PauseSoundCmd,
        ResumeSoundCmd,
        SetSoundVolumeCmd,
        SetSoundPitchCmd,
        PlayMusicStreamCmd,
        UpdateMusicStreamCmd,
        StopMusicStreamCmd,
        PauseMusicStreamCmd,
        ResumeMusicStreamCmd,
        SetMusicVolumeCmd
    >;

    class CommandBufferBuilder {
        std::vector<Command> queue;

    public:
        CommandBufferBuilder() = default;

        explicit CommandBufferBuilder(const size_t initial_capacity) {
            queue.reserve(initial_capacity);
        }

        template <typename T>
        void push(T&& command) {
            static_assert(
                std::is_constructible_v<Command, T>,
                "Type provided is not a supported command in the variant queue."
            );
            queue.push_back(std::forward<T>(command));
        }

        void reserve(const size_t capacity) {
            queue.reserve(capacity);
        }

        void clear_background(const Color color = RAYWHITE) {
            queue.emplace_back(ClearBackgroundCmd{ .color = color });
        }

        void start_mode_2d(const Camera2D &camera) {
            queue.emplace_back(BeginMode2DCmd{ camera });
        }

        void end_mode_2d() {
            queue.emplace_back(EndMode2DCmd{});
        }

        void draw_fps(const Vector2 pos) {
            queue.emplace_back(DrawFPSCmd{ .position = pos });
        }

        void draw_circle(const Vector2 center, const float radius, const Color color) {
            queue.emplace_back(DrawCircleCmd{ .center = center, .radius = radius, .color = color });
        }

        void draw_rectangle(const Rectangle rect, const Color color) {
            queue.emplace_back(DrawRectangleCmd{ .rect = rect, .color = color });
        }

        void draw_pixel(const Vector2 pos, const Color color) {
            queue.emplace_back(DrawPixelCmd{ .position = pos, .color = color });
        }

        // Added thickness parameter (defaulted to 1.0f)
        void draw_line(const Vector2 start, const Vector2 end, const Color color, const float thickness = 1.0f) {
            queue.emplace_back(DrawLineCmd{ .start = start, .end = end, .thickness = thickness, .color = color });
        }

        // Added missing p3 parameter
        void draw_triangle(const Vector2 p1, const Vector2 p2, const Vector2 p3, const Color color) {
            queue.emplace_back(DrawTriangleCmd{ .p1 = p1, .p2 = p2, .p3 = p3, .color = color });
        }

        void draw_ellipse(const Vector2 center, const float radH, const float radV, const Color color) {
            queue.emplace_back(DrawEllipseCmd{ .center = center, .radius_h = radH, .radius_v = radV, .color = color });
        }

        // Added missing spacing parameter (defaulted to 1.0f)
        void draw_text(std::string text, const Vector2 pos, const Font &font_face, const float size, const Color color, const float spacing = 1.0f) {
            queue.emplace_back(DrawTextCmd{
                .text = std::move(text),
                .position = pos,
                .font_face = font_face,
                .font_size = size,
                .spacing = spacing,
                .color = color
            });
        }

        void draw_texture(const Texture2D& texture, const Vector2 pos, const Color tint = WHITE) {
            queue.emplace_back(DrawTextureCmd{ .texture = texture, .position = pos, .tint = tint });
        }

        void draw_texture_rec(const Texture2D& texture, const Rectangle source, const Vector2 pos, const Color tint = WHITE) {
            queue.emplace_back(DrawTextureRecCmd{ .texture = texture, .source = source, .position = pos, .tint = tint });
        }

        // Removed position parameter from DrawTexturePro helper
        void draw_texture_pro(const Texture2D& texture, const Rectangle source, const Rectangle dest, const Vector2 origin, const float rotation, const Color tint = WHITE) {
            queue.emplace_back(DrawTextureProCmd{
                .texture = texture,
                .source = source,
                .dest = dest,
                .origin = origin,
                .rotation = rotation,
                .tint = tint
            });
        }

        void draw_poly(const Vector2 center, const int sides, const float radius, const float rotation, const Color color) {
            queue.emplace_back(DrawPolyCmd{ .center = center, .sides = sides, .radius = radius, .rotation = rotation, .color = color });
        }

        // Sound Helpers
        void play_sound(const Sound& sound) { queue.emplace_back(PlaySoundCmd{ sound }); }
        void stop_sound(const Sound& sound) { queue.emplace_back(StopSoundCmd{ sound }); }
        void pause_sound(const Sound& sound) { queue.emplace_back(PauseSoundCmd{ sound }); }
        void resume_sound(const Sound& sound) { queue.emplace_back(ResumeSoundCmd{ sound }); }
        void set_sound_volume(const Sound& sound, const float volume) { queue.emplace_back(SetSoundVolumeCmd{ sound, volume }); }
        void set_sound_pitch(const Sound& sound, const float pitch) { queue.emplace_back(SetSoundPitchCmd{ sound, pitch }); }

        // Music Helpers
        void play_music_stream(const Music& music) { queue.emplace_back(PlayMusicStreamCmd{ music }); }
        void update_music_stream(const Music& music) { queue.emplace_back(UpdateMusicStreamCmd{ music }); }
        void stop_music_stream(const Music& music) { queue.emplace_back(StopMusicStreamCmd{ music }); }
        void pause_music_stream(const Music& music) { queue.emplace_back(PauseMusicStreamCmd{ music }); }
        void resume_music_stream(const Music& music) { queue.emplace_back(ResumeMusicStreamCmd{ music }); }
        void set_music_volume(const Music& music, const float volume) { queue.emplace_back(SetMusicVolumeCmd{ music, volume }); }

        [[nodiscard]] const std::vector<Command>& get_commands() const { return queue; }
        void clear() { queue.clear(); }
        [[nodiscard]] bool empty() const { return queue.empty(); }
        [[nodiscard]] size_t size() const { return queue.size(); }
    };

}