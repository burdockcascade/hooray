#include "hooray/assets/font.hpp"
#include <raylib.h>
#include "../raylibtools.hpp"

namespace hooray {

    Font::Font(const std::string& path, const int base_size) noexcept {
        if (!::IsWindowReady()) return;
        const ::Font raw = ::LoadFontEx(path.c_str(), base_size, nullptr, 0);
        handle_ = {
            .base_size = raw.baseSize,
            .glyph_count = raw.glyphCount,
            .glyph_padding = raw.glyphPadding,
            .texture = {
                .id = raw.texture.id,
                .width = raw.texture.width,
                .height = raw.texture.height,
                .format = raw.texture.format,
                .mipmaps = raw.texture.mipmaps
            },
            .recs = raw.recs,
            .glyphs = raw.glyphs
        };
    }

    Font::~Font() noexcept {
        if (is_valid()) {
            ::UnloadFont(to_raylib_font(handle_));
            handle_ = {};
        }
    }

    auto Font::operator=(Font&& other) noexcept -> Font& {
        if (this != &other) {
            if (is_valid()) {
                ::UnloadFont(to_raylib_font(handle_));
            }
            handle_ = std::exchange(other.handle_, FontHandle{});
        }
        return *this;
    }

}