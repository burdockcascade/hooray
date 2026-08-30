#include <algorithm>
#include <cmath>
#include "hr_types.hpp"

namespace Hooray {

    Vector4 Color::ToVector4() const noexcept {
        return Vector4{r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f};
    }

    std::uint32_t Color::ToInt() const noexcept {
        return (static_cast<std::uint32_t>(r) << 24) |
               (static_cast<std::uint32_t>(g) << 16) |
               (static_cast<std::uint32_t>(b) << 8) |
               (static_cast<std::uint32_t>(a));
    }

    Color Color::FromNormalized(Vector4 normalized) noexcept {
        return Color{
            static_cast<int>(normalized.x * 255.0f),
            static_cast<int>(normalized.y * 255.0f),
            static_cast<int>(normalized.z * 255.0f),
            static_cast<int>(normalized.w * 255.0f)
        };
    }

    Color Color::FromHSV(float hue, float saturation, float value) noexcept {
        float c = value * saturation;
        float h = std::fmod(std::max(0.0f, hue) / 60.0f, 6.0f);
        float x = c * (1.0f - std::abs(std::fmod(h, 2.0f) - 1.0f));
        float m = value - c;

        float rf = 0.0f, gf = 0.0f, bf = 0.0f;
        if (h >= 0.0f && h < 1.0f) { rf = c; gf = x; bf = 0.0f; }
        else if (h >= 1.0f && h < 2.0f) { rf = x; gf = c; bf = 0.0f; }
        else if (h >= 2.0f && h < 3.0f) { rf = 0.0f; gf = c; bf = x; }
        else if (h >= 3.0f && h < 4.0f) { rf = 0.0f; gf = x; bf = c; }
        else if (h >= 4.0f && h < 5.0f) { rf = x; gf = 0.0f; bf = c; }
        else if (h >= 5.0f && h < 6.0f) { rf = c; gf = 0.0f; bf = x; }

        return Color{
            static_cast<int>((rf + m) * 255.0f),
            static_cast<int>((gf + m) * 255.0f),
            static_cast<int>((bf + m) * 255.0f),
            255
        };
    }

    Vector3 Color::ToHSV() const noexcept {
        float rf = r / 255.0f;
        float gf = g / 255.0f;
        float bf = b / 255.0f;

        float max = std::max({rf, gf, bf});
        float min = std::min({rf, gf, bf});
        float delta = max - min;

        float hue = 0.0f;
        if (delta > 0.0f) {
            if (max == rf) { hue = 60.0f * std::fmod((gf - bf) / delta, 6.0f); }
            else if (max == gf) { hue = 60.0f * ((bf - rf) / delta + 2.0f); }
            else if (max == bf) { hue = 60.0f * ((rf - gf) / delta + 4.0f); }
        }
        if (hue < 0.0f) { hue += 360.0f; }

        float saturation = (max == 0.0f) ? 0.0f : (delta / max);
        return Vector3{hue, saturation, max};
    }

    Color Color::GetFade(float alpha) const noexcept {
        return Color{r, g, b, static_cast<unsigned char>(a * std::clamp(alpha, 0.0f, 1.0f))};
    }

    Color Color::GetAlpha(float alpha) const noexcept {
        return Color{r, g, b, static_cast<unsigned char>(std::clamp(alpha, 0.0f, 1.0f) * 255.0f)};
    }

    Color Color::GetAlphaBlend(Color src, Color tint) const noexcept {
        // Standard alpha composite blending (this = dst background)
        float srcA = (src.a / 255.0f) * (tint.a / 255.0f);
        float dstA = a / 255.0f;
        float outA = srcA + dstA * (1.0f - srcA);

        if (outA == 0.0f) return Color{0, 0, 0, 0};

        auto blendComponent = [&](unsigned char dstC, unsigned char srcC, unsigned char tintC) {
            float s = (srcC / 255.0f) * (tintC / 255.0f);
            float d = dstC / 255.0f;
            return static_cast<unsigned char>(((s * srcA + d * dstA * (1.0f - srcA)) / outA) * 255.0f);
        };

        return Color{
            blendComponent(r, src.r, tint.r),
            blendComponent(g, src.g, tint.g),
            blendComponent(b, src.b, tint.b),
            static_cast<unsigned char>(outA * 255.0f)
        };
    }

    Color Color::GetLerp(Color target, float factor) const noexcept {
        float t = std::clamp(factor, 0.0f, 1.0f);
        return Color{
            static_cast<int>(r + t * (target.r - r)),
            static_cast<int>(g + t * (target.g - g)),
            static_cast<int>(b + t * (target.b - b)),
            static_cast<int>(a + t * (target.a - a))
        };
    }

    Color Color::GetTint(Color tint) const noexcept {
        return Color{
            static_cast<int>((r * tint.r) / 255.0f),
            static_cast<int>((g * tint.g) / 255.0f),
            static_cast<int>((b * tint.b) / 255.0f),
            static_cast<int>((a * tint.a) / 255.0f)
        };
    }

    Color Color::GetContrast(float contrast) const noexcept {
        float f = (259.0f * (contrast + 255.0f)) / (255.0f * (259.0f - contrast));

        auto applyContrast = [f](unsigned char c) {
            float val = f * (static_cast<float>(c) - 128.0f) + 128.0f;
            return static_cast<unsigned char>(std::clamp(val, 0.0f, 255.0f));
        };

        return Color{applyContrast(r), applyContrast(g), applyContrast(b), a};
    }

    Color Color::GetBrightness(float factor) const noexcept {
        auto applyBrightness = [factor](unsigned char c) {
            float val = static_cast<float>(c) + (factor * 255.0f);
            return static_cast<unsigned char>(std::clamp(val, 0.0f, 255.0f));
        };

        return Color{applyBrightness(r), applyBrightness(g), applyBrightness(b), a};
    }

    Color& Color::ApplyFade(float alpha) noexcept {
        *this = GetFade(alpha);
        return *this;
    }

    Color& Color::ApplyAlpha(float alpha) noexcept {
        *this = GetAlpha(alpha);
        return *this;
    }

    Color& Color::ApplyTint(Color tint) noexcept {
        *this = GetTint(tint);
        return *this;
    }

    Color& Color::ApplyContrast(float contrast) noexcept {
        *this = GetContrast(contrast);
        return *this;
    }

    Color& Color::ApplyBrightness(float factor) noexcept {
        *this = GetBrightness(factor);
        return *this;
    }
}
