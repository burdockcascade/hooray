#include <raylib.h>
#include <raymath.h>
#include <hooray/math.hpp>
#include "conversion.hpp"

namespace Hooray {

#pragma region Vector2

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

#pragma region Vector4

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

#pragma endregion

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

}