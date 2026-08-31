#include "conversion.hpp"
#include "hr_types.hpp"
#include "raylib.h"
#include "raymath.h"

namespace Hooray {

#pragma region Vector2

    // --- Vector2 Operators ---
    Vector2 Vector2::operator+(Vector2 rhs) const noexcept {
        return FromRay(::Vector2Add(ToRay(*this), ToRay(rhs)));
    }

    Vector2 Vector2::operator-(Vector2 rhs) const noexcept {
        return FromRay(::Vector2Subtract(ToRay(*this), ToRay(rhs)));
    }

    Vector2 Vector2::operator*(Vector2 rhs) const noexcept {
        return FromRay(::Vector2Multiply(ToRay(*this), ToRay(rhs)));
    }

    Vector2 Vector2::operator*(float scalar) const noexcept {
        return FromRay(::Vector2Scale(ToRay(*this), scalar));
    }

    Vector2 Vector2::operator/(Vector2 rhs) const noexcept {
        return FromRay(::Vector2Divide(ToRay(*this), ToRay(rhs)));
    }

    Vector2 Vector2::operator/(float scalar) const noexcept {
        return FromRay(::Vector2Scale(ToRay(*this), 1.0f / scalar));
    }

    Vector2 Vector2::operator-() const noexcept {
        return FromRay(::Vector2Negate(ToRay(*this)));
    }

    Vector2 &Vector2::operator+=(Vector2 rhs) noexcept {
        *this = *this + rhs;
        return *this;
    }

    Vector2 &Vector2::operator-=(Vector2 rhs) noexcept {
        *this = *this - rhs;
        return *this;
    }

    Vector2 &Vector2::operator*=(Vector2 rhs) noexcept {
        *this = *this * rhs;
        return *this;
    }

    Vector2 &Vector2::operator*=(float scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }

    Vector2 &Vector2::operator/=(Vector2 rhs) noexcept {
        *this = *this / rhs;
        return *this;
    }

    Vector2 &Vector2::operator/=(float scalar) noexcept {
        *this = *this / scalar;
        return *this;
    }

    Vector2 operator*(float scalar, Vector2 vec) noexcept {
        return vec * scalar;
    }

    float Vector2::get_angle(Vector2 other) const noexcept {
        return ::Vector2Angle(ToRay(*this), ToRay(other));
    }

    Vector2 Vector2::get_rotated(float angleRad) const noexcept {
        return FromRay(::Vector2Rotate(ToRay(*this), angleRad));
    }

    Vector2& Vector2::apply_rotate(float angleRad) noexcept {
        *this = get_rotated(angleRad);
        return *this;
    }

#pragma endregion

#pragma region Vector3

    // --- Vector3 Operators ---
    Vector3 Vector3::operator+(Vector3 rhs) const noexcept {
        return FromRay(::Vector3Add(ToRay(*this), ToRay(rhs)));
    }

    Vector3 Vector3::operator-(Vector3 rhs) const noexcept {
        return FromRay(::Vector3Subtract(ToRay(*this), ToRay(rhs)));
    }

    Vector3 Vector3::operator*(Vector3 rhs) const noexcept {
        return FromRay(::Vector3Multiply(ToRay(*this), ToRay(rhs)));
    }

    Vector3 Vector3::operator*(float scalar) const noexcept {
        return FromRay(::Vector3Scale(ToRay(*this), scalar));
    }

    Vector3 Vector3::operator/(Vector3 rhs) const noexcept {
        return FromRay(::Vector3Divide(ToRay(*this), ToRay(rhs)));
    }

    Vector3 Vector3::operator/(float scalar) const noexcept {
        return FromRay(::Vector3Scale(ToRay(*this), 1.0f / scalar));
    }

    Vector3 Vector3::operator-() const noexcept {
        return FromRay(::Vector3Negate(ToRay(*this)));
    }

    Vector3 &Vector3::operator+=(Vector3 rhs) noexcept {
        *this = *this + rhs;
        return *this;
    }

    Vector3 &Vector3::operator-=(Vector3 rhs) noexcept {
        *this = *this - rhs;
        return *this;
    }

    Vector3 &Vector3::operator*=(Vector3 rhs) noexcept {
        *this = *this * rhs;
        return *this;
    }

    Vector3 &Vector3::operator*=(float scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }

    Vector3 &Vector3::operator/=(Vector3 rhs) noexcept {
        *this = *this / rhs;
        return *this;
    }

    Vector3 &Vector3::operator/=(float scalar) noexcept {
        *this = *this / scalar;
        return *this;
    }

    Vector3 operator*(float scalar, Vector3 vec) noexcept {
        return vec * scalar;
    }

    float Vector3::get_angle(Vector3 other) const noexcept {
        return ::Vector3Angle(ToRay(*this), ToRay(other));
    }

#pragma endregion

    // --- Vector4 Operators ---
    Vector4 Vector4::operator+(Vector4 rhs) const noexcept {
        return FromRay(::Vector4Add(ToRay(*this), ToRay(rhs)));
    }

    Vector4 Vector4::operator-(Vector4 rhs) const noexcept {
        return FromRay(::Vector4Subtract(ToRay(*this), ToRay(rhs)));
    }

    Vector4 Vector4::operator*(Vector4 rhs) const noexcept {
        return FromRay(::Vector4Multiply(ToRay(*this), ToRay(rhs)));
    }

    Vector4 Vector4::operator*(float scalar) const noexcept {
        return FromRay(::Vector4Scale(ToRay(*this), scalar));
    }

    Vector4 Vector4::operator/(Vector4 rhs) const noexcept {
        return FromRay(::Vector4Divide(ToRay(*this), ToRay(rhs)));
    }

    Vector4 Vector4::operator/(float scalar) const noexcept {
        return FromRay(::Vector4Scale(ToRay(*this), 1.0f / scalar));
    }

    Vector4 Vector4::operator-() const noexcept {
        return FromRay(::Vector4Negate(ToRay(*this)));
    }

    Vector4 &Vector4::operator+=(Vector4 rhs) noexcept {
        *this = *this + rhs;
        return *this;
    }

    Vector4 &Vector4::operator-=(Vector4 rhs) noexcept {
        *this = *this - rhs;
        return *this;
    }

    Vector4 &Vector4::operator*=(Vector4 rhs) noexcept {
        *this = *this * rhs;
        return *this;
    }

    Vector4 &Vector4::operator*=(float scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }

    Vector4 &Vector4::operator/=(Vector4 rhs) noexcept {
        *this = *this / rhs;
        return *this;
    }

    Vector4 &Vector4::operator/=(float scalar) noexcept {
        *this = *this / scalar;
        return *this;
    }

    Vector4 operator*(float scalar, Vector4 vec) noexcept { return vec * scalar; }

#pragma region Matrix

    // Static Transformation Methods
    Matrix Matrix::translate(float x, float y, float z) noexcept {
        return FromRay(::MatrixTranslate(x, y, z));
    }

    Matrix Matrix::translate(Vector3 v) noexcept {
        return FromRay(::MatrixTranslate(v.x, v.y, v.z));
    }

    Matrix Matrix::scale(float x, float y, float z) noexcept {
        return FromRay(::MatrixScale(x, y, z));
    }

    Matrix Matrix::rotate_x(float angleRad) noexcept {
        return FromRay(::MatrixRotateX(angleRad));
    }

    Matrix Matrix::rotate_y(float angleRad) noexcept {
        return FromRay(::MatrixRotateY(angleRad));
    }

    Matrix Matrix::rotate_z(float angleRad) noexcept {
        return FromRay(::MatrixRotateZ(angleRad));
    }

    Matrix Matrix::rotate(Vector3 axis, float angleRad) noexcept {
        return FromRay(::MatrixRotate(ToRay(axis), angleRad));
    }

    Matrix Matrix::perspective(double fovY, double aspect, double nearPlane, double farPlane) noexcept {
        return FromRay(::MatrixPerspective(fovY, aspect, nearPlane, farPlane));
    }

    Matrix Matrix::ortho(double left, double right, double bottom, double top, double nearPlane, double farPlane) noexcept {
        return FromRay(::MatrixOrtho(left, right, bottom, top, nearPlane, farPlane));
    }

    // Matrix Inspection & Inverse Methods
    float Matrix::get_determinant() const noexcept {
        return ::MatrixDeterminant(ToRay(*this));
    }

    Matrix Matrix::get_transposed() const noexcept {
        return FromRay(::MatrixTranspose(ToRay(*this)));
    }

    Matrix Matrix::get_inverted() const noexcept {
        return FromRay(::MatrixInvert(ToRay(*this)));
    }

    // In-place Modifier Methods
    Matrix& Matrix::apply_transpose() noexcept {
        *this = get_transposed();
        return *this;
    }

    Matrix& Matrix::apply_invert() noexcept {
        *this = get_inverted();
        return *this;
    }

    Matrix Matrix::operator+(Matrix rhs) const noexcept {
        return FromRay(::MatrixAdd(ToRay(*this), ToRay(rhs)));
    }

    Matrix Matrix::operator-(Matrix rhs) const noexcept {
        return FromRay(::MatrixSubtract(ToRay(*this), ToRay(rhs)));
    }

    Matrix Matrix::operator*(Matrix rhs) const noexcept {
        return FromRay(::MatrixMultiply(ToRay(*this), ToRay(rhs)));
    }

    Matrix &Matrix::operator+=(Matrix rhs) noexcept {
        *this = *this + rhs;
        return *this;
    }

    Matrix &Matrix::operator-=(Matrix rhs) noexcept {
        *this = *this - rhs;
        return *this;
    }

    Matrix &Matrix::operator*=(Matrix rhs) noexcept {
        *this = *this * rhs;
        return *this;
    }

    bool Matrix::operator==(const Matrix& rhs) const noexcept {
        return m0 == rhs.m0 && m4 == rhs.m4 && m8  == rhs.m8  && m12 == rhs.m12 &&
               m1 == rhs.m1 && m5 == rhs.m5 && m9  == rhs.m9  && m13 == rhs.m13 &&
               m2 == rhs.m2 && m6 == rhs.m6 && m10 == rhs.m10 && m14 == rhs.m14 &&
               m3 == rhs.m3 && m7 == rhs.m7 && m11 == rhs.m11 && m15 == rhs.m15;
    }

#pragma endregion

#pragma region Rectangle

    // --- Geometry ---
    bool Rectangle::contains(Vector2 point) const noexcept {
        return CheckCollisionPointRec(ToRay(point), ToRay(*this));
    }

    bool Rectangle::overlaps(Rectangle other) const noexcept {
        return CheckCollisionRecs(ToRay(*this), ToRay(other));
    }

    Rectangle Rectangle::get_collision(Rectangle other) const noexcept {
        return FromRay(GetCollisionRec(ToRay(*this), ToRay(other)));
    }

#pragma endregion

#pragma region Circle

    bool Circle::contains(const Vector2 other) const {
        return ::CheckCollisionPointCircle(ToRay(other), ToRay(this->center), this->radius);
    }

    bool Circle::overlaps(const Circle other) const {
        return ::CheckCollisionCircles(ToRay(this->center), this->radius, ToRay(other.center), other.radius);
    }

    bool Circle::overlaps(const Rectangle other) const {
        return ::CheckCollisionCircleRec(ToRay(this->center), this->radius, ToRay(other));
    }

#pragma endregion

#pragma region Color Methods

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

#pragma endregion

}