#include <raylib.h>
#include "hooray/scenegraph.hpp"
#include "raylibtools.hpp"

namespace Hooray {

    Texture::Texture(const std::filesystem::path& path) noexcept {
        const ::Texture2D raw = ::LoadTexture(path.string().c_str());
        handle_ = {
            .id = raw.id,
            .width = raw.width,
            .height = raw.height,
            .format = raw.format,
            .mipmaps = raw.mipmaps
        };
    }

    Texture::~Texture() noexcept {
        if (handle_.id > 0) {
            ::UnloadTexture(ToRaylibTexture(handle_));
            handle_ = {};
        }
    }

    auto Texture::operator=(Texture&& other) noexcept -> Texture& {
        if (this != &other) {
            if (handle_.id > 0) {
                ::UnloadTexture(ToRaylibTexture(handle_));
            }
            handle_ = std::exchange(other.handle_, TextureHandle{});
        }
        return *this;
    }

    Font::Font(const std::filesystem::path& path, const int baseSize) noexcept {
        const ::Font raw = ::LoadFontEx(path.string().c_str(), baseSize, nullptr, 0);
        handle_ = {
            .baseSize = raw.baseSize,
            .glyphCount = raw.glyphCount,
            .glyphPadding = raw.glyphPadding,
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
        if (handle_.baseSize > 0) {
            ::UnloadFont(ToRaylibFont(handle_));
            handle_ = {};
        }
    }

    auto Font::operator=(Font&& other) noexcept -> Font& {
        if (this != &other) {
            if (handle_.baseSize > 0) {
                ::UnloadFont(ToRaylibFont(handle_));
            }
            handle_ = std::exchange(other.handle_, FontHandle{});
        }
        return *this;
    }

}