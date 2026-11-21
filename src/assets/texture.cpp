#include "hooray/assets/texture.hpp"
#include <raylib.h>
#include "../raylibtools.hpp"

namespace hooray {

    Texture::Texture(const std::string& path) noexcept {
        if (!::IsWindowReady()) return;
        const ::Texture2D raw = ::LoadTexture(path.c_str());
        handle_ = {
            .id = raw.id,
            .width = raw.width,
            .height = raw.height,
            .format = raw.format,
            .mipmaps = raw.mipmaps
        };
    }

    Texture::~Texture() noexcept {
        if (is_valid()) {
            ::UnloadTexture(to_raylib_texture(handle_));
            handle_ = {};
        }
    }

    auto Texture::operator=(Texture&& other) noexcept -> Texture& {
        if (this != &other) {
            if (is_valid()) {
                ::UnloadTexture(to_raylib_texture(handle_));
            }
            handle_ = std::exchange(other.handle_, TextureHandle{});
        }
        return *this;
    }

}