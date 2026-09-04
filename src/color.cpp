#include "conversion.hpp"
#include "raylib.h"
#include "raymath.h"

#include <hooray/handles.hpp>
#include <hooray/math.hpp>
#include <hooray/geometry.hpp>
#include <hooray/color.hpp>
#include <hooray/window.hpp>

namespace Hooray {

    Vector4 Color::to_vector4() const noexcept {
        return FromRay(::ColorNormalize(ToRay(*this)));
    }

    std::uint32_t Color::to_int() const noexcept {
        return ::ColorToInt(ToRay(*this));
    }

    Color Color::from_normalized(Vector4 normalized) noexcept {
        return FromRay(::ColorFromNormalized(ToRay(normalized)));
    }

    Color Color::from_hsv(float hue, float saturation, float value) noexcept {
        return FromRay(::ColorFromHSV(hue, saturation, value));
    }

    Vector3 Color::to_hsv() const noexcept {
        return FromRay(::ColorToHSV(ToRay(*this)));
    }

    Color Color::get_fade(float alpha) const noexcept {
        return FromRay(::Fade(ToRay(*this), alpha));
    }

    Color Color::get_alpha(float alpha) const noexcept {
        Color result = *this;
        result.a = static_cast<unsigned char>(std::clamp(alpha, 0.0f, 1.0f) * 255.0f);
        return result;
    }

    Color Color::get_alpha_blend(Color src, Color tint) const noexcept {
        return FromRay(::ColorAlphaBlend(ToRay(*this), ToRay(src), ToRay(tint)));
    }

    Color Color::get_lerp(Color target, float factor) const noexcept {
        return FromRay(::ColorLerp(ToRay(*this), ToRay(target), factor));
    }

    Color Color::get_tint(Color tint) const noexcept {
        return FromRay(::ColorTint(ToRay(*this), ToRay(tint)));
    }

    Color Color::get_contrast(float contrast) const noexcept {
        return FromRay(::ColorContrast(ToRay(*this), contrast));
    }

    Color Color::get_brightness(float factor) const noexcept {
        return FromRay(::ColorBrightness(ToRay(*this), factor));
    }

    Color& Color::apply_fade(float alpha) noexcept {
        *this = get_fade(alpha);
        return *this;
    }

    Color& Color::apply_alpha(float alpha) noexcept {
        *this = get_alpha(alpha);
        return *this;
    }

    Color& Color::apply_tint(Color tint) noexcept {
        *this = get_tint(tint);
        return *this;
    }

    Color& Color::apply_contrast(float contrast) noexcept {
        *this = get_contrast(contrast);
        return *this;
    }

    Color& Color::apply_brightness(float factor) noexcept {
        *this = get_brightness(factor);
        return *this;
    }

}