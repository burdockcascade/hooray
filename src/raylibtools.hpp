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

}