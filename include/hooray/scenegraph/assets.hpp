#pragma once
#include <filesystem>
#include <variant>

namespace Hooray {

    struct TextureHandle {
        uint32_t id{0};
        int width{0};
        int height{0};
        int format{0};
        int mipmaps{0};
    };

    class Texture {
    public:
        explicit Texture(const std::filesystem::path& path) noexcept;
        explicit constexpr Texture(TextureHandle handle = {}) noexcept : handle_{handle} {}

        ~Texture() noexcept;

        // Move-only semantics
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

    struct FontHandle {
        int baseSize{0};
        int glyphCount{0};
        int glyphPadding{0};
        TextureHandle texture{};
        void* recs{nullptr};
        void* glyphs{nullptr};
    };

    class Font {
    public:
        explicit Font(const std::filesystem::path& path, int baseSize) noexcept;
        explicit constexpr Font(FontHandle handle = {}) noexcept : handle_{handle} {}

        ~Font() noexcept;

        Font(const Font&) = delete;
        auto operator=(const Font&) -> Font& = delete;

        constexpr Font(Font&& other) noexcept
            : handle_{std::exchange(other.handle_, FontHandle{})} {}

        auto operator=(Font&& other) noexcept -> Font&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.baseSize > 0;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const FontHandle& {
            return handle_;
        }

    private:
        FontHandle handle_{};
    };

    struct TextureAsset {
        std::string id;
        std::filesystem::path path;
    };

    struct FontAsset {
        std::string id;
        std::filesystem::path path;
        int baseSize{32};
    };

    using Asset = std::variant<TextureAsset, FontAsset>;

}
