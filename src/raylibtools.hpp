#pragma once
#include <raylib.h>

namespace Hooray {
    inline ::Color ToRaylibColor(Color c) {
        return ::Color{.r = c.r, .g = c.g, .b = c.b, .a = c.a};
    }

    inline ::Camera2D ToRaylibCamera2D(const Camera2D& cam) {
        return ::Camera2D{
            .offset = {.x = cam.offset.x, .y = cam.offset.y},
            .target = {.x = cam.target.x, .y = cam.target.y},
            .rotation = cam.rotation,
            .zoom = cam.zoom
        };
    }

    inline ::Font ToRaylibFont(const FontHandle& h) noexcept {
        return ::Font{
            .baseSize = h.baseSize,
            .glyphCount = h.glyphCount,
            .glyphPadding = h.glyphPadding,
            .texture = ::Texture2D{
                .id = h.texture.id,
                .width = h.texture.width,
                .height = h.texture.height,
                .mipmaps = h.texture.mipmaps,
                .format = h.texture.format
            },
            .recs = static_cast<::Rectangle*>(h.recs),
            .glyphs = static_cast<::GlyphInfo*>(h.glyphs)
        };
    }

    inline ::Texture2D ToRaylibTexture(const TextureHandle& handle) {
        return ::Texture2D{
            .id = handle.id,
            .width = handle.width,
            .height = handle.height,
            .mipmaps = handle.mipmaps,
            .format = handle.format
        };
    }

    inline ::Vector2 ToRaylibVector2(const Vector2& vec) noexcept {
        return ::Vector2{.x = vec.x, .y = vec.y};
    }

    // Conversion helpers to raylib types
    inline auto ToRaylibSound(const SoundHandle& h) noexcept -> ::Sound {
        return ::Sound{
            .stream = {
                .buffer = static_cast<rAudioBuffer*>(h.stream.buffer),
                .processor = static_cast<rAudioProcessor*>(h.stream.processor),
                .sampleRate = h.stream.sampleRate,
                .sampleSize = h.stream.sampleSize,
                .channels = h.stream.channels
            },
            .frameCount = h.frameCount
        };
    }

    inline auto ToRaylibMusic(const MusicHandle& h) noexcept -> ::Music {
        return ::Music{
            .stream = {
                .buffer = static_cast<rAudioBuffer*>(h.stream.buffer),
                .processor = static_cast<rAudioProcessor*>(h.stream.processor),
                .sampleRate = h.stream.sampleRate,
                .sampleSize = h.stream.sampleSize,
                .channels = h.stream.channels
            },
            .frameCount = h.frameCount,
            .looping = h.looping,
            .ctxType = h.ctxType,
            .ctxData = h.ctxData
        };
    }

}