#pragma once
#include "../include/types.hpp"

struct Color;
struct Vector2;
struct Vector3;
struct Vector4;
struct Matrix;
struct Rectangle;
struct Camera2D;
struct Font;
struct Texture;
struct Sound;
struct Music;

namespace Hooray {

    ::Color ToRay(Color c) noexcept;
    Color FromRay(::Color c) noexcept;

    ::Vector2 ToRay(Vector2 v) noexcept;
    Vector2 FromRay(::Vector2 v) noexcept;

    ::Vector3 ToRay(Vector3 v) noexcept;
    Vector3 FromRay(::Vector3 v) noexcept;

    ::Vector4 ToRay(Vector4 v) noexcept;
    Vector4 FromRay(::Vector4 v) noexcept;

    ::Matrix ToRay(Matrix m) noexcept;
    Matrix FromRay(::Matrix m) noexcept;

    ::Rectangle ToRay(Rectangle r) noexcept;
    Rectangle FromRay(::Rectangle r) noexcept;

    ::Camera2D ToRay(Camera2D c) noexcept;

    ::Font ToRay(FontHandle f) noexcept;
    ::Texture ToRay(TextureHandle t) noexcept;
    ::Sound ToRay(SoundHandle s) noexcept;
    ::Music ToRay(MusicHandle m) noexcept;

}