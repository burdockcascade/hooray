#pragma once

#include <algorithm>
#include <cmath>
#include <ostream>

namespace Hooray {

    class Vector2 {
    public:
        float x{0.0f};
        float y{0.0f};

        constexpr Vector2() noexcept = default;
        constexpr Vector2(float val) noexcept : x{val}, y{val} {}
        constexpr Vector2(float x_, float y_) noexcept : x{x_}, y{y_} {}

        [[nodiscard]] static constexpr Vector2 zero() noexcept { return {0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector2 one() noexcept { return {1.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector2 up() noexcept { return {0.0f, -1.0f}; }
        [[nodiscard]] static constexpr Vector2 down() noexcept { return {0.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector2 left() noexcept { return {-1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector2 right() noexcept { return {1.0f, 0.0f}; }

        [[nodiscard]] float get_length() const noexcept { return std::sqrt(x * x + y * y); }
        [[nodiscard]] constexpr float get_length_sqr() const noexcept { return x * x + y * y; }
        [[nodiscard]] float get_distance(Vector2 other) const noexcept { return (*this - other).get_length(); }
        [[nodiscard]] constexpr float get_distance_sqr(Vector2 other) const noexcept { return (*this - other).get_length_sqr(); }
        [[nodiscard]] float get_angle(Vector2 other) const noexcept;

        [[nodiscard]] Vector2 get_normalized() const noexcept {
            float len = get_length();
            return (len > 0.0f) ? Vector2{x / len, y / len} : Vector2{0.0f, 0.0f};
        }
        [[nodiscard]] Vector2 get_rotated(float angleRad) const noexcept;
        [[nodiscard]] constexpr Vector2 get_lerp(Vector2 target, float amount) const noexcept {
            return {x + amount * (target.x - x), y + amount * (target.y - y)};
        }
        [[nodiscard]] constexpr Vector2 get_clamp(Vector2 min, Vector2 max) const noexcept {
            return {std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y)};
        }

        [[nodiscard]] constexpr float get_dot(Vector2 other) const noexcept { return x * other.x + y * other.y; }
        [[nodiscard]] constexpr float get_cross(Vector2 other) const noexcept { return x * other.y - y * other.x; }

        Vector2& apply_normalize() noexcept {
            float len = get_length();
            if (len > 0.0f) { x /= len; y /= len; }
            return *this;
        }
        Vector2& apply_rotate(float angleRad) noexcept;

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

        [[nodiscard]] static constexpr Vector3 zero() noexcept { return {0.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 one() noexcept { return {1.0f, 1.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector3 up() noexcept { return {0.0f, 1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 down() noexcept { return {0.0f, -1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 left() noexcept { return {-1.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 right() noexcept { return {1.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 forward() noexcept { return {0.0f, 0.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector3 back() noexcept { return {0.0f, 0.0f, -1.0f}; }

        [[nodiscard]] float get_length() const noexcept { return std::sqrt(x * x + y * y + z * z); }
        [[nodiscard]] constexpr float get_length_sqr() const noexcept { return x * x + y * y + z * z; }
        [[nodiscard]] float get_distance(Vector3 other) const noexcept { return (*this - other).get_length(); }
        [[nodiscard]] constexpr float get_distance_sqr(Vector3 other) const noexcept { return (*this - other).get_length_sqr(); }
        [[nodiscard]] float get_angle(Vector3 other) const noexcept;

        [[nodiscard]] Vector3 get_normalized() const noexcept {
            float len = get_length();
            return (len > 0.0f) ? Vector3{x / len, y / len, z / len} : Vector3{0.0f, 0.0f, 0.0f};
        }
        [[nodiscard]] constexpr Vector3 get_lerp(Vector3 target, float amount) const noexcept {
            return {x + amount * (target.x - x), y + amount * (target.y - y), z + amount * (target.z - z)};
        }
        [[nodiscard]] constexpr Vector3 get_clamp(Vector3 min, Vector3 max) const noexcept {
            return {std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y), std::clamp(z, min.z, max.z)};
        }

        [[nodiscard]] constexpr float get_dot(Vector3 other) const noexcept { return x * other.x + y * other.y + z * other.z; }
        [[nodiscard]] constexpr Vector3 get_cross(Vector3 other) const noexcept {
            return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
        }

        Vector3& apply_normalize() noexcept {
            float len = get_length();
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

        [[nodiscard]] static constexpr Vector4 zero() noexcept { return {0.0f, 0.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector4 one() noexcept { return {1.0f, 1.0f, 1.0f, 1.0f}; }

        [[nodiscard]] float get_length() const noexcept { return std::sqrt(x * x + y * y + z * z + w * w); }
        [[nodiscard]] constexpr float get_length_sqr() const noexcept { return x * x + y * y + z * z + w * w; }
        [[nodiscard]] float get_distance(Vector4 other) const noexcept { return (*this - other).get_length(); }
        [[nodiscard]] constexpr float get_distance_sqr(Vector4 other) const noexcept { return (*this - other).get_length_sqr(); }

        [[nodiscard]] Vector4 get_normalized() const noexcept {
            float len = get_length();
            return (len > 0.0f) ? Vector4{x / len, y / len, z / len, w / len} : Vector4{0.0f, 0.0f, 0.0f, 0.0f};
        }
        [[nodiscard]] constexpr Vector4 get_lerp(Vector4 target, float amount) const noexcept {
            return {x + amount * (target.x - x), y + amount * (target.y - y),
                    z + amount * (target.z - z), w + amount * (target.w - w)};
        }

        [[nodiscard]] constexpr float get_dot(Vector4 other) const noexcept { return x * other.x + y * other.y + z * other.z + w * other.w; }

        Vector4& apply_normalize() noexcept {
            float len = get_length();
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

        [[nodiscard]] static constexpr Matrix identity() noexcept { return Matrix{}; }
        [[nodiscard]] static Matrix translate(float x, float y, float z) noexcept;
        [[nodiscard]] static Matrix translate(Vector3 v) noexcept;
        [[nodiscard]] static Matrix scale(float x, float y, float z) noexcept;
        [[nodiscard]] static Matrix rotate_x(float angleRad) noexcept;
        [[nodiscard]] static Matrix rotate_y(float angleRad) noexcept;
        [[nodiscard]] static Matrix rotate_z(float angleRad) noexcept;
        [[nodiscard]] static Matrix rotate(Vector3 axis, float angleRad) noexcept;
        [[nodiscard]] static Matrix perspective(double fovY, double aspect, double nearPlane, double farPlane) noexcept;
        [[nodiscard]] static Matrix ortho(double left, double right, double bottom, double top, double nearPlane, double farPlane) noexcept;

        [[nodiscard]] float get_determinant() const noexcept;
        [[nodiscard]] Matrix get_transposed() const noexcept;
        [[nodiscard]] Matrix get_inverted() const noexcept;

        Matrix& apply_transpose() noexcept;
        Matrix& apply_invert() noexcept;

        Matrix operator+(Matrix rhs) const noexcept;
        Matrix operator-(Matrix rhs) const noexcept;
        Matrix operator*(Matrix rhs) const noexcept;

        Matrix& operator+=(Matrix rhs) noexcept;
        Matrix& operator-=(Matrix rhs) noexcept;
        Matrix& operator*=(Matrix rhs) noexcept;

        bool operator==(const Matrix& rhs) const noexcept;
    };

    Vector2 operator*(float scalar, Vector2 vec) noexcept;
    Vector3 operator*(float scalar, Vector3 vec) noexcept;
    Vector4 operator*(float scalar, Vector4 vec) noexcept;

}