#pragma once

#include <vector>
#include <variant>
#include <type_traits>
#include <string>
#include <types.hpp>

namespace Hooray {

    // ==========================================
    // State Commands
    // ==========================================

    struct ClearBackgroundCmd {
        Color color{ 255, 255, 255, 255 };
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
        FontHandle font_face;
        float font_size;
        float spacing;
        Color color;
    };

    struct DrawTextureCmd {
        TextureHandle texture;
        Vector2 position;
        Color tint;
    };

    struct DrawTextureRecCmd {
        TextureHandle texture;
        Rectangle source;
        Vector2 position;
        Color tint;
    };

    struct DrawTextureProCmd {
        TextureHandle texture;
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
        SoundHandle sound;
    };

    struct StopSoundCmd {
        SoundHandle sound;
    };

    struct PauseSoundCmd {
        SoundHandle sound;
    };

    struct ResumeSoundCmd {
        SoundHandle sound;
    };

    struct SetSoundVolumeCmd {
        SoundHandle sound;
        float volume;
    };

    struct SetSoundPitchCmd {
        SoundHandle sound;
        float pitch;
    };

    struct PlayMusicStreamCmd {
        MusicHandle music;
    };

    struct UpdateMusicStreamCmd {
        MusicHandle music;
    };

    struct StopMusicStreamCmd {
        MusicHandle music;
    };

    struct PauseMusicStreamCmd {
        MusicHandle music;
    };

    struct ResumeMusicStreamCmd {
        MusicHandle music;
    };

    struct SetMusicVolumeCmd {
        MusicHandle music;
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

}