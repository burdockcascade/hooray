#pragma once
#include <raylib.h>
#include <hooray/scenegraph/camera.hpp>

#include "hooray/core/assets.hpp"

namespace hooray {
    inline ::Color to_raylib_color(Color c) {
        return ::Color{.r = c.r, .g = c.g, .b = c.b, .a = c.a};
    }

    inline ::Camera2D to_raylib_camera2d(const Camera2D& cam) {
        return ::Camera2D{
            .offset = {.x = cam.get_offset().x, .y = cam.get_offset().y},
            .target = {.x = cam.get_target().x, .y = cam.get_target().y},
            .rotation = cam.get_rotation(),
            .zoom = cam.get_zoom()
        };
    }

    inline ::Font to_raylib_font(const FontHandle& h) noexcept {
        return ::Font{
            .baseSize = h.base_size,
            .glyphCount = h.glyph_count,
            .glyphPadding = h.glyph_padding,
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

    inline ::Texture2D to_raylib_texture(const TextureHandle& handle) {
        return ::Texture2D{
            .id = handle.id,
            .width = handle.width,
            .height = handle.height,
            .mipmaps = handle.mipmaps,
            .format = handle.format
        };
    }

    inline ::Vector2 to_raylib_vector2(const Vector2& vec) noexcept {
        return ::Vector2{.x = vec.x, .y = vec.y};
    }

    // Conversion helpers to raylib types
    inline ::Sound to_raylib_sound(const SoundHandle& h) noexcept {
        return ::Sound{
            .stream = {
                .buffer = static_cast<rAudioBuffer*>(h.stream.buffer),
                .processor = static_cast<rAudioProcessor*>(h.stream.processor),
                .sampleRate = h.stream.sample_rate,
                .sampleSize = h.stream.sample_size,
                .channels = h.stream.channels
            },
            .frameCount = h.frame_count,
        };
    }

    inline ::Music to_raylib_music(const MusicHandle& h) noexcept {
        return ::Music{
            .stream = {
                .buffer = static_cast<rAudioBuffer*>(h.stream.buffer),
                .processor = static_cast<rAudioProcessor*>(h.stream.processor),
                .sampleRate = h.stream.sample_rate,
                .sampleSize = h.stream.sample_size,
                .channels = h.stream.channels
            },
            .frameCount = h.frame_count,
            .looping = h.looping,
            .ctxType = h.ctx_type,
            .ctxData = h.ctx_data
        };
    }

}
