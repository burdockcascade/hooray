#pragma once
#include <types.hpp>
#include <raylib.h>

namespace Hooray {

    // Helper casting helpers for standard Raylib types
    constexpr ::Color ToRay(Color c) noexcept {
        return ::Color{ .r = c.r, .g = c.g, .b = c.b, .a = c.a };
    }

    constexpr Color FromRay(::Color c) noexcept {
        return Color{ c.r, c.g, c.b, c.a };
    }

    constexpr ::Vector2 ToRay(Vector2 v) noexcept {
        return ::Vector2{ .x = v.x, .y = v.y };
    }

    constexpr Vector2 FromRay(::Vector2 v) noexcept {
        return Vector2{ v.x, v.y };
    }

    constexpr ::Vector3 ToRay(Vector3 v) noexcept {
        return ::Vector3{ .x = v.x, .y = v.y, .z = v.z };
    }

    constexpr Vector3 FromRay(::Vector3 v) noexcept {
        return Vector3{ v.x, v.y, v.z };
    }

    constexpr ::Vector4 ToRay(Vector4 v) noexcept {
        return ::Vector4{ .x = v.x, .y = v.y, .z = v.z, .w = v.w };
    }

    constexpr Vector4 FromRay(::Vector4 v) noexcept {
        return Vector4{ v.x, v.y, v.z, v.w };
    }

    constexpr ::Matrix ToRay(Matrix m) noexcept {
        return ::Matrix{
            .m0 = m.m0, .m4 = m.m4, .m8 = m.m8,  .m12 = m.m12,
            .m1 = m.m1, .m5 = m.m5, .m9 = m.m9,  .m13 = m.m13,
            .m2 = m.m2, .m6 = m.m6, .m10 = m.m10, .m14 = m.m14,
            .m3 = m.m3, .m7 = m.m7, .m11 = m.m11, .m15 = m.m15
        };
    }

    constexpr Matrix FromRay(::Matrix m) noexcept {
        return Matrix{
            m.m0, m.m4, m.m8,  m.m12,
            m.m1, m.m5, m.m9,  m.m13,
            m.m2, m.m6, m.m10, m.m14,
            m.m3, m.m7, m.m11, m.m15
        };
    }

    constexpr ::Rectangle ToRay(Rectangle r) noexcept {
        return ::Rectangle{ .x = r.x, .y = r.y, .width = r.width, .height = r.height };
    }

    constexpr Rectangle FromRay(::Rectangle r) noexcept {
        return Rectangle{ r.x, r.y, r.width, r.height };
    }

    constexpr ::Camera2D ToRay(Camera2D c) noexcept {
        return ::Camera2D{
            .offset = ToRay(c.offset),
            .target = ToRay(c.target),
            .rotation = c.rotation,
            .zoom = c.zoom
        };
    }

    constexpr ::Font ToRay(FontHandle f) noexcept {
        return *reinterpret_cast<::Font*>(&f);
    }

    constexpr ::Texture ToRay(TextureHandle t) noexcept {
        return *reinterpret_cast<::Texture*>(&t);
    }

    constexpr ::Sound ToRay(SoundHandle s) noexcept {
        return *reinterpret_cast<::Sound*>(&s);
    }

    constexpr ::Music ToRay(MusicHandle m) noexcept {
        return *reinterpret_cast<::Music*>(&m);
    }

}