#pragma once

#include <algorithm>
#include <cstdint>

namespace Hooray {

    class Color {
    public:
        unsigned char r{0};
        unsigned char g{0};
        unsigned char b{0};
        unsigned char a{255};

        // Constructors
        constexpr Color() noexcept = default;
        constexpr Color(int r_, int g_, int b_, int a_ = 255) noexcept {
            r = static_cast<unsigned char>(std::clamp(r_, 0, 255));
            g = static_cast<unsigned char>(std::clamp(g_, 0, 255));
            b = static_cast<unsigned char>(std::clamp(b_, 0, 255));
            a = static_cast<unsigned char>(std::clamp(a_, 0, 255));
        }

        constexpr Color(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255) noexcept {
            r = r_;
            g = g_;
            b = b_;
            a = a_;
        }

        explicit constexpr Color(std::uint32_t hexValue) noexcept
            : r{static_cast<unsigned char>((hexValue >> 24) & 0xFF)},
              g{static_cast<unsigned char>((hexValue >> 16) & 0xFF)},
              b{static_cast<unsigned char>((hexValue >> 8) & 0xFF)},
              a{static_cast<unsigned char>(hexValue & 0xFF)} {}

        // Declarations requiring Raylib implementation in CPP
        [[nodiscard]] Vector4 to_vector4() const noexcept;
        [[nodiscard]] std::uint32_t to_int() const noexcept;
        [[nodiscard]] static Color from_normalized(Vector4 normalized) noexcept;
        [[nodiscard]] static Color from_hsv(float hue, float saturation, float value) noexcept;
        [[nodiscard]] Vector3 to_hsv() const noexcept;

        [[nodiscard]] Color get_fade(float alpha) const noexcept;
        [[nodiscard]] Color get_alpha(float alpha) const noexcept;
        [[nodiscard]] Color get_alpha_blend(Color src, Color tint) const noexcept;
        [[nodiscard]] Color get_lerp(Color target, float factor) const noexcept;
        [[nodiscard]] Color get_tint(Color tint) const noexcept;
        [[nodiscard]] Color get_contrast(float contrast) const noexcept;
        [[nodiscard]] Color get_brightness(float factor) const noexcept;

        Color& apply_fade(float alpha) noexcept;
        Color& apply_alpha(float alpha) noexcept;
        Color& apply_tint(Color tint) noexcept;
        Color& apply_contrast(float contrast) noexcept;
        Color& apply_brightness(float factor) noexcept;

        constexpr bool operator==(const Color& rhs) const noexcept {
            return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
        }
    };

    namespace Palette {
        // Grays & Neutrals
        constexpr Color White{255, 255, 255, 255};
        constexpr Color Snow{255, 250, 250, 255};
        constexpr Color Ivory{255, 255, 240, 255};
        constexpr Color RayWhite{245, 245, 245, 255};
        constexpr Color OffWhite{238, 238, 228, 255};
        constexpr Color Gainsboro{220, 220, 220, 255};
        constexpr Color LightGray{200, 200, 200, 255};
        constexpr Color Silver{192, 192, 192, 255};
        constexpr Color Gray{130, 130, 130, 255};
        constexpr Color Slate{112, 128, 144, 255};
        constexpr Color DarkGray{80, 80, 80, 255};
        constexpr Color CharBlack{30, 30, 30, 255};
        constexpr Color Black{0, 0, 0, 255};
        constexpr Color Blank{0, 0, 0, 0};

        // Reds, Pinks & Oranges
        constexpr Color Salmon{250, 128, 114, 255};
        constexpr Color Coral{255, 127, 80, 255};
        constexpr Color Tomato{255, 99, 71, 255};
        constexpr Color Crimson{180, 10, 30, 255};
        constexpr Color Red{230, 41, 55, 255};
        constexpr Color PureRed{255, 0, 0, 255};
        constexpr Color Scarlet{255, 36, 0, 255};
        constexpr Color Maroon{190, 33, 55, 255};
        constexpr Color Burgundy{128, 0, 32, 255};
        constexpr Color Peach{255, 218, 185, 255};
        constexpr Color Orange{255, 161, 0, 255};
        constexpr Color DarkOrange{255, 140, 0, 255};
        constexpr Color Amber{255, 191, 0, 255};
        constexpr Color Gold{255, 203, 0, 255};
        constexpr Color Yellow{253, 249, 0, 255};
        constexpr Color Lemon{255, 247, 0, 255};
        constexpr Color Rose{255, 192, 203, 255};
        constexpr Color Pink{255, 109, 194, 255};
        constexpr Color HotPink{255, 20, 147, 255};
        constexpr Color DeepPink{255, 20, 147, 255};
        constexpr Color Magenta{255, 0, 255, 255};
        constexpr Color Fuchsia{224, 17, 95, 255};

        // Greens & Teals
        constexpr Color Mint{152, 251, 152, 255};
        constexpr Color PastelGreen{119, 221, 119, 255};
        constexpr Color Lime{0, 158, 47, 255};
        constexpr Color LimeGreen{50, 205, 50, 255};
        constexpr Color NeonGreen{57, 255, 20, 255};
        constexpr Color Green{0, 228, 48, 255};
        constexpr Color PureGreen{0, 255, 0, 255};
        constexpr Color Emerald{80, 200, 120, 255};
        constexpr Color DarkGreen{0, 117, 44, 255};
        constexpr Color Forest{34, 139, 34, 255};
        constexpr Color Pine{1, 121, 111, 255};
        constexpr Color Olive{128, 128, 0, 255};
        constexpr Color Turquoise{64, 224, 208, 255};
        constexpr Color Teal{0, 128, 128, 255};
        constexpr Color SeaGreen{46, 139, 87, 255};

        // Blues & Cyans
        constexpr Color ElectricBlue{125, 249, 255, 255};
        constexpr Color Cyan{0, 255, 255, 255};
        constexpr Color Aqua{0, 255, 255, 255};
        constexpr Color PastelBlue{174, 198, 207, 255};
        constexpr Color SkyBlue{102, 191, 255, 255};
        constexpr Color DeepSkyBlue{0, 191, 255, 255};
        constexpr Color Cornflower{100, 149, 237, 255};
        constexpr Color Blue{0, 121, 241, 255};
        constexpr Color PureBlue{0, 0, 255, 255};
        constexpr Color RoyalBlue{65, 105, 225, 255};
        constexpr Color DarkBlue{0, 82, 172, 255};
        constexpr Color Navy{0, 0, 128, 255};
        constexpr Color MidnightBlue{25, 25, 112, 255};

        // Purples & Violets
        constexpr Color Lavender{230, 230, 250, 255};
        constexpr Color Lilac{200, 162, 200, 255};
        constexpr Color Purple{200, 122, 255, 255};
        constexpr Color PurePurple{128, 0, 128, 255};
        constexpr Color Amethyst{153, 102, 204, 255};
        constexpr Color Violet{135, 60, 190, 255};
        constexpr Color Indigo{75, 0, 130, 255};
        constexpr Color DarkPurple{112, 31, 126, 255};
        constexpr Color Plum{142, 69, 133, 255};
        constexpr Color Orchid{218, 112, 214, 255};

        // Browns & Earth Tones
        constexpr Color Wheat{245, 222, 179, 255};
        constexpr Color Beige{211, 176, 131, 255};
        constexpr Color Tan{210, 180, 140, 255};
        constexpr Color Sand{194, 178, 128, 255};
        constexpr Color Khaki{189, 183, 107, 255};
        constexpr Color Terracotta{226, 114, 91, 255};
        constexpr Color Bronze{205, 127, 50, 255};
        constexpr Color Copper{184, 115, 51, 255};
        constexpr Color Rust{183, 65, 14, 255};
        constexpr Color Brown{127, 106, 91, 255};
        constexpr Color SaddleBrown{139, 69, 19, 255};
        constexpr Color DarkBrown{76, 63, 47, 255};
        constexpr Color Coffee{111, 78, 55, 255};
        constexpr Color Chocolate{210, 105, 30, 255};
    }

}