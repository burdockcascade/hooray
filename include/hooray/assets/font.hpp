#pragma once
#include <string>
#include <utility>

#include "texture.hpp"

namespace hooray {

    struct FontHandle {
        int base_size{0};
        int glyph_count{0};
        int glyph_padding{0};
        TextureHandle texture{};
        void* recs{nullptr};
        void* glyphs{nullptr};
    };

    class Font {
    public:
        explicit Font(const std::string& path, int base_size) noexcept;
        explicit constexpr Font(FontHandle handle = {}) noexcept : handle_{handle} {}

        ~Font() noexcept;

        Font(const Font&) = delete;
        auto operator=(const Font&) -> Font& = delete;

        constexpr Font(Font&& other) noexcept
            : handle_{std::exchange(other.handle_, FontHandle{})} {}

        auto operator=(Font&& other) noexcept -> Font&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.texture.id > 0 && handle_. base_size > 0;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const FontHandle& {
            return handle_;
        }

    private:
        FontHandle handle_{};
    };

    struct FontAsset {
        std::string id;
        std::string path;
        int base_size{32};
    };

}