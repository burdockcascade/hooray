#include <raylib.h>
#include "hooray/scenegraph.hpp"

namespace Hooray {

    Texture::Texture(const std::filesystem::path& path) noexcept {
        ::Texture2D raw = ::LoadTexture(path.string().c_str());
        handle_ = std::bit_cast<TextureHandle>(raw);
    }

    Texture::~Texture() noexcept {
        if (handle_.id > 0) {
            ::UnloadTexture(std::bit_cast<::Texture2D>(handle_));
            handle_ = {};
        }
    }

    auto Texture::operator=(Texture&& other) noexcept -> Texture& {
        if (this != &other) {
            if (handle_.id > 0) {
                ::UnloadTexture(std::bit_cast<::Texture2D>(handle_));
            }
            handle_ = std::exchange(other.handle_, TextureHandle{});
        }
        return *this;
    }

}