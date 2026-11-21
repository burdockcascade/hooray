#pragma once
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace hooray {

    struct TextureHandle {
        uint32_t id{0};
        int width{0};
        int height{0};
        int format{0};
        int mipmaps{0};
    };

    class Texture {
    public:
        explicit Texture(const std::string& path) noexcept;
        explicit constexpr Texture(TextureHandle handle = {}) noexcept : handle_{handle} {}

        ~Texture() noexcept;

        Texture(const Texture&) = delete;
        auto operator=(const Texture&) -> Texture& = delete;

        constexpr Texture(Texture&& other) noexcept
            : handle_{std::exchange(other.handle_, TextureHandle{})} {}

        auto operator=(Texture&& other) noexcept -> Texture&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.id > 0;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const TextureHandle& {
            return handle_;
        }

    private:
        TextureHandle handle_{};
    };

    struct TextureAsset {
        std::string id;
        std::string path;
    };

    struct TextureRegion {
        float x{0.0f};
        float y{0.0f};
        float width{0.0f};
        float height{0.0f};
    };

    struct Spritesheet {
        Texture texture{};
        float frame_width{0.0f};
        float frame_height{0.0f};
        std::vector<TextureRegion> regions;
    };

    struct AtlasAsset {
        std::string id;
        std::string path;
        std::vector<TextureRegion> regions{};
    };

    struct SpritesheetAsset {
        std::string id;
        std::string path;
        float frame_width{0.0f};
        float frame_height{0.0f};
        std::vector<TextureRegion> regions{};
    };

}