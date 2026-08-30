#pragma once

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <concepts>
#include <ostream>
#include <vector>

namespace Hooray {
    // Forward declarations
    class Vector3;
    class Vector4;

#pragma region Color

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
        [[nodiscard]] Vector4 ToVector4() const noexcept;
        [[nodiscard]] std::uint32_t ToInt() const noexcept;
        [[nodiscard]] static Color FromNormalized(Vector4 normalized) noexcept;
        [[nodiscard]] static Color FromHSV(float hue, float saturation, float value) noexcept;
        [[nodiscard]] Vector3 ToHSV() const noexcept;

        [[nodiscard]] Color GetFade(float alpha) const noexcept;
        [[nodiscard]] Color GetAlpha(float alpha) const noexcept;
        [[nodiscard]] Color GetAlphaBlend(Color src, Color tint) const noexcept;
        [[nodiscard]] Color GetLerp(Color target, float factor) const noexcept;
        [[nodiscard]] Color GetTint(Color tint) const noexcept;
        [[nodiscard]] Color GetContrast(float contrast) const noexcept;
        [[nodiscard]] Color GetBrightness(float factor) const noexcept;

        Color& ApplyFade(float alpha) noexcept;
        Color& ApplyAlpha(float alpha) noexcept;
        Color& ApplyTint(Color tint) noexcept;
        Color& ApplyContrast(float contrast) noexcept;
        Color& ApplyBrightness(float factor) noexcept;

        constexpr bool operator==(const Color& rhs) const noexcept {
            return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
        }
    };

#pragma endregion

#pragma region Math

    class Vector2 {
    public:
        float x{0.0f};
        float y{0.0f};

        constexpr Vector2() noexcept = default;
        constexpr Vector2(float val) noexcept : x{val}, y{val} {}
        constexpr Vector2(float x_, float y_) noexcept : x{x_}, y{y_} {}

        [[nodiscard]] static constexpr Vector2 Zero() noexcept { return {0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector2 One() noexcept { return {1.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector2 Up() noexcept { return {0.0f, -1.0f}; }
        [[nodiscard]] static constexpr Vector2 Down() noexcept { return {0.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector2 Left() noexcept { return {-1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector2 Right() noexcept { return {1.0f, 0.0f}; }

        [[nodiscard]] float GetLength() const noexcept { return std::sqrt(x * x + y * y); }
        [[nodiscard]] constexpr float GetLengthSqr() const noexcept { return x * x + y * y; }
        [[nodiscard]] float GetDistance(Vector2 other) const noexcept { return (*this - other).GetLength(); }
        [[nodiscard]] constexpr float GetDistanceSqr(Vector2 other) const noexcept { return (*this - other).GetLengthSqr(); }
        [[nodiscard]] float GetAngle(Vector2 other) const noexcept;

        [[nodiscard]] Vector2 GetNormalized() const noexcept {
            float len = GetLength();
            return (len > 0.0f) ? Vector2{x / len, y / len} : Vector2{0.0f, 0.0f};
        }
        [[nodiscard]] Vector2 GetRotated(float angleRad) const noexcept;
        [[nodiscard]] constexpr Vector2 GetLerp(Vector2 target, float amount) const noexcept {
            return {x + amount * (target.x - x), y + amount * (target.y - y)};
        }
        [[nodiscard]] constexpr Vector2 GetClamp(Vector2 min, Vector2 max) const noexcept {
            return {std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y)};
        }

        [[nodiscard]] constexpr float GetDot(Vector2 other) const noexcept { return x * other.x + y * other.y; }
        [[nodiscard]] constexpr float GetCross(Vector2 other) const noexcept { return x * other.y - y * other.x; }

        Vector2& ApplyNormalize() noexcept {
            float len = GetLength();
            if (len > 0.0f) { x /= len; y /= len; }
            return *this;
        }
        Vector2& ApplyRotate(float angleRad) noexcept;

        // Operators implemented in CPP via raymath
        Vector2 operator+(Vector2 rhs) const noexcept;
        Vector2 operator-(Vector2 rhs) const noexcept;
        Vector2 operator*(Vector2 rhs) const noexcept;
        Vector2 operator*(float scalar) const noexcept;
        Vector2 operator/(Vector2 rhs) const noexcept;
        Vector2 operator/(float scalar) const noexcept;
        Vector2 operator-() const noexcept;

        Vector2& operator+=(Vector2 rhs) noexcept;
        Vector2& operator-=(Vector2 rhs) noexcept;
        Vector2& operator*=(Vector2 rhs) noexcept;
        Vector2& operator*=(float scalar) noexcept;
        Vector2& operator/=(Vector2 rhs) noexcept;
        Vector2& operator/=(float scalar) noexcept;

        bool operator==(const Vector2& rhs) const noexcept = default;

    };

    class Vector3 {
    public:
        float x{0.0f};
        float y{0.0f};
        float z{0.0f};

        constexpr Vector3() noexcept = default;
        constexpr Vector3(float val) noexcept : x{val}, y{val}, z{val} {}
        constexpr Vector3(float x_, float y_, float z_) noexcept : x{x_}, y{y_}, z{z_} {}

        [[nodiscard]] static constexpr Vector3 Zero() noexcept { return {0.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 One() noexcept { return {1.0f, 1.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector3 Up() noexcept { return {0.0f, 1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Down() noexcept { return {0.0f, -1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Left() noexcept { return {-1.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Right() noexcept { return {1.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Forward() noexcept { return {0.0f, 0.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector3 Back() noexcept { return {0.0f, 0.0f, -1.0f}; }

        [[nodiscard]] float GetLength() const noexcept { return std::sqrt(x * x + y * y + z * z); }
        [[nodiscard]] constexpr float GetLengthSqr() const noexcept { return x * x + y * y + z * z; }
        [[nodiscard]] float GetDistance(Vector3 other) const noexcept { return (*this - other).GetLength(); }
        [[nodiscard]] constexpr float GetDistanceSqr(Vector3 other) const noexcept { return (*this - other).GetLengthSqr(); }
        [[nodiscard]] float GetAngle(Vector3 other) const noexcept;

        [[nodiscard]] Vector3 GetNormalized() const noexcept {
            float len = GetLength();
            return (len > 0.0f) ? Vector3{x / len, y / len, z / len} : Vector3{0.0f, 0.0f, 0.0f};
        }
        [[nodiscard]] constexpr Vector3 GetLerp(Vector3 target, float amount) const noexcept {
            return {x + amount * (target.x - x), y + amount * (target.y - y), z + amount * (target.z - z)};
        }
        [[nodiscard]] constexpr Vector3 GetClamp(Vector3 min, Vector3 max) const noexcept {
            return {std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y), std::clamp(z, min.z, max.z)};
        }

        [[nodiscard]] constexpr float GetDot(Vector3 other) const noexcept { return x * other.x + y * other.y + z * other.z; }
        [[nodiscard]] constexpr Vector3 GetCross(Vector3 other) const noexcept {
            return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
        }

        Vector3& ApplyNormalize() noexcept {
            float len = GetLength();
            if (len > 0.0f) { x /= len; y /= len; z /= len; }
            return *this;
        }

        // Operators implemented in CPP via raymath
        Vector3 operator+(Vector3 rhs) const noexcept;
        Vector3 operator-(Vector3 rhs) const noexcept;
        Vector3 operator*(Vector3 rhs) const noexcept;
        Vector3 operator*(float scalar) const noexcept;
        Vector3 operator/(Vector3 rhs) const noexcept;
        Vector3 operator/(float scalar) const noexcept;
        Vector3 operator-() const noexcept;

        Vector3& operator+=(Vector3 rhs) noexcept;
        Vector3& operator-=(Vector3 rhs) noexcept;
        Vector3& operator*=(Vector3 rhs) noexcept;
        Vector3& operator*=(float scalar) noexcept;
        Vector3& operator/=(Vector3 rhs) noexcept;
        Vector3& operator/=(float scalar) noexcept;

        bool operator==(const Vector3& rhs) const noexcept = default;

    };

    class Vector4 {
    public:
        float x{0.0f};
        float y{0.0f};
        float z{0.0f};
        float w{0.0f};

        constexpr Vector4() noexcept = default;
        constexpr Vector4(float val) noexcept : x{val}, y{val}, z{val}, w{val} {}
        constexpr Vector4(float x_, float y_, float z_, float w_) noexcept : x{x_}, y{y_}, z{z_}, w{w_} {}

        [[nodiscard]] static constexpr Vector4 Zero() noexcept { return {0.0f, 0.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector4 One() noexcept { return {1.0f, 1.0f, 1.0f, 1.0f}; }

        [[nodiscard]] float GetLength() const noexcept { return std::sqrt(x * x + y * y + z * z + w * w); }
        [[nodiscard]] constexpr float GetLengthSqr() const noexcept { return x * x + y * y + z * z + w * w; }
        [[nodiscard]] float GetDistance(Vector4 other) const noexcept { return (*this - other).GetLength(); }
        [[nodiscard]] constexpr float GetDistanceSqr(Vector4 other) const noexcept { return (*this - other).GetLengthSqr(); }

        [[nodiscard]] Vector4 GetNormalized() const noexcept {
            float len = GetLength();
            return (len > 0.0f) ? Vector4{x / len, y / len, z / len, w / len} : Vector4{0.0f, 0.0f, 0.0f, 0.0f};
        }
        [[nodiscard]] constexpr Vector4 GetLerp(Vector4 target, float amount) const noexcept {
            return {x + amount * (target.x - x), y + amount * (target.y - y),
                    z + amount * (target.z - z), w + amount * (target.w - w)};
        }

        [[nodiscard]] constexpr float GetDot(Vector4 other) const noexcept { return x * other.x + y * other.y + z * other.z + w * other.w; }

        Vector4& ApplyNormalize() noexcept {
            float len = GetLength();
            if (len > 0.0f) { x /= len; y /= len; z /= len; w /= len; }
            return *this;
        }

        // Operators implemented in CPP via raymath
        Vector4 operator+(Vector4 rhs) const noexcept;
        Vector4 operator-(Vector4 rhs) const noexcept;
        Vector4 operator*(Vector4 rhs) const noexcept;
        Vector4 operator*(float scalar) const noexcept;
        Vector4 operator/(Vector4 rhs) const noexcept;
        Vector4 operator/(float scalar) const noexcept;
        Vector4 operator-() const noexcept;

        Vector4& operator+=(Vector4 rhs) noexcept;
        Vector4& operator-=(Vector4 rhs) noexcept;
        Vector4& operator*=(Vector4 rhs) noexcept;
        Vector4& operator*=(float scalar) noexcept;
        Vector4& operator/=(Vector4 rhs) noexcept;
        Vector4& operator/=(float scalar) noexcept;

        bool operator==(const Vector4& rhs) const noexcept = default;

    };

    class Matrix {
    public:
        float m0{1.0f}, m4{0.0f}, m8{0.0f},  m12{0.0f};
        float m1{0.0f}, m5{1.0f}, m9{0.0f},  m13{0.0f};
        float m2{0.0f}, m6{0.0f}, m10{1.0f}, m14{0.0f};
        float m3{0.0f}, m7{0.0f}, m11{0.0f}, m15{1.0f};

        constexpr Matrix() noexcept = default;
        constexpr Matrix(float m0_, float m4_, float m8_,  float m12_,
                         float m1_, float m5_, float m9_,  float m13_,
                         float m2_, float m6_, float m10_, float m14_,
                         float m3_, float m7_, float m11_, float m15_) noexcept
            : m0{m0_}, m4{m4_}, m8{m8_},   m12{m12_},
              m1{m1_}, m5{m5_}, m9{m9_},   m13{m13_},
              m2{m2_}, m6{m6_}, m10{m10_}, m14{m14_},
              m3{m3_}, m7{m7_}, m11{m11_}, m15{m15_} {}

        constexpr float operator[](std::size_t row, std::size_t col) const noexcept {
            return (&m0)[row * 4 + col];
        }
        constexpr float& operator[](std::size_t row, std::size_t col) noexcept {
            return (&m0)[row * 4 + col];
        }

        [[nodiscard]] static constexpr Matrix Identity() noexcept { return Matrix{}; }
        [[nodiscard]] static Matrix Translate(float x, float y, float z) noexcept;
        [[nodiscard]] static Matrix Translate(Vector3 v) noexcept;
        [[nodiscard]] static Matrix Scale(float x, float y, float z) noexcept;
        [[nodiscard]] static Matrix RotateX(float angleRad) noexcept;
        [[nodiscard]] static Matrix RotateY(float angleRad) noexcept;
        [[nodiscard]] static Matrix RotateZ(float angleRad) noexcept;
        [[nodiscard]] static Matrix Rotate(Vector3 axis, float angleRad) noexcept;
        [[nodiscard]] static Matrix Perspective(double fovY, double aspect, double nearPlane, double farPlane) noexcept;
        [[nodiscard]] static Matrix Ortho(double left, double right, double bottom, double top, double nearPlane, double farPlane) noexcept;

        [[nodiscard]] float GetDeterminant() const noexcept;
        [[nodiscard]] Matrix GetTransposed() const noexcept;
        [[nodiscard]] Matrix GetInverted() const noexcept;

        Matrix& ApplyTranspose() noexcept;
        Matrix& ApplyInvert() noexcept;

        Matrix operator+(Matrix rhs) const noexcept;
        Matrix operator-(Matrix rhs) const noexcept;
        Matrix operator*(Matrix rhs) const noexcept;

        Matrix& operator+=(Matrix rhs) noexcept;
        Matrix& operator-=(Matrix rhs) noexcept;
        Matrix& operator*=(Matrix rhs) noexcept;

        constexpr bool operator==(const Matrix& rhs) const noexcept {
            return m0 == rhs.m0 && m4 == rhs.m4 && m8  == rhs.m8  && m12 == rhs.m12 &&
                   m1 == rhs.m1 && m5 == rhs.m5 && m9  == rhs.m9  && m13 == rhs.m13 &&
                   m2 == rhs.m2 && m6 == rhs.m6 && m10 == rhs.m10 && m14 == rhs.m14 &&
                   m3 == rhs.m3 && m7 == rhs.m7 && m11 == rhs.m11 && m15 == rhs.m15;
        }
    };

    Vector2 operator*(float scalar, Vector2 vec) noexcept;
    Vector3 operator*(float scalar, Vector3 vec) noexcept;
    Vector4 operator*(float scalar, Vector4 vec) noexcept;

#pragma endregion

#pragma region Geometry

    class Rectangle {
    public:
        float x{0.0f};
        float y{0.0f};
        float width{0.0f};
        float height{0.0f};

        constexpr Rectangle() noexcept = default;
        constexpr Rectangle(float x_, float y_, float width_, float height_) noexcept: x{x_}, y{y_}, width{width_}, height{height_} {}
        constexpr Rectangle(Vector2 position, Vector2 size) noexcept: x{position.x}, y{position.y}, width{size.x}, height{size.y} {}

        [[nodiscard]] constexpr Vector2 GetPosition() const noexcept { return {x, y}; }
        constexpr void SetPosition(Vector2 pos) noexcept { x = pos.x; y = pos.y; }

        [[nodiscard]] constexpr Vector2 GetSize() const noexcept { return {width, height}; }
        constexpr void SetSize(Vector2 size) noexcept { width = size.x; height = size.y; }

        [[nodiscard]] constexpr float Left() const noexcept { return x; }
        [[nodiscard]] constexpr float Right() const noexcept { return x + width; }
        [[nodiscard]] constexpr float Top() const noexcept { return y; }
        [[nodiscard]] constexpr float Bottom() const noexcept { return y + height; }
        [[nodiscard]] constexpr Vector2 Center() const noexcept { return {x + width * 0.5f, y + height * 0.5f}; }

        [[nodiscard]] bool Contains(Vector2 point) const noexcept;
        [[nodiscard]] bool Overlaps(Rectangle other) const noexcept;
        [[nodiscard]] Rectangle GetCollision(Rectangle other) const noexcept;

        constexpr bool operator==(const Rectangle& rhs) const noexcept {
            return x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height;
        }

    };

    struct Circle {
        Vector2 center;
        float radius;

        constexpr Circle() noexcept = default;
        constexpr Circle(Vector2 center_, float radius_) noexcept : center{center_}, radius{radius_} {}
        constexpr Circle(float x, float y, float radius_) noexcept : center{x, y}, radius{radius_} {}

        [[nodiscard]] bool contains(Vector2 other) const;
        [[nodiscard]] bool overlaps(Circle other) const;
        [[nodiscard]] bool overlaps(Rectangle other) const;
    };

    struct JSTriangle {
        Vector2 v1;
        Vector2 v2;
        Vector2 v3;
    };

    struct JSPoint {
        Vector2 position;
    };

    struct JSLine {
        Vector2 start;
        Vector2 end;
    };

    struct JSPolygon {
        std::vector<Vector2> points;
    };

#pragma endregion

    struct Camera2D {
        Vector2 offset;
        Vector2 target;
        float rotation;
        float zoom;
    };

    struct TextureHandle { void* id{ nullptr }; };
    struct FontHandle    { void* id{ nullptr }; };
    struct SoundHandle   { void* id{ nullptr }; };
    struct MusicHandle   { void* id{ nullptr }; };

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