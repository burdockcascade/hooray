#include "conversion.hpp"
#include "hoo_types.hpp"
#include "raylib.h"
#include "raymath.h"

namespace Hooray {
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
    Matrix Matrix::Translate(float x, float y, float z) noexcept {
        return FromRay(::MatrixTranslate(x, y, z));
    }

    Matrix Matrix::Translate(Vector3 v) noexcept {
        return FromRay(::MatrixTranslate(v.x, v.y, v.z));
    }

    Matrix Matrix::Scale(float x, float y, float z) noexcept {
        return FromRay(::MatrixScale(x, y, z));
    }

    Matrix Matrix::RotateX(float angleRad) noexcept {
        return FromRay(::MatrixRotateX(angleRad));
    }

    Matrix Matrix::RotateY(float angleRad) noexcept {
        return FromRay(::MatrixRotateY(angleRad));
    }

    Matrix Matrix::RotateZ(float angleRad) noexcept {
        return FromRay(::MatrixRotateZ(angleRad));
    }

    Matrix Matrix::Rotate(Vector3 axis, float angleRad) noexcept {
        return FromRay(::MatrixRotate(ToRay(axis), angleRad));
    }

    Matrix Matrix::Perspective(double fovY, double aspect, double nearPlane, double farPlane) noexcept {
        return FromRay(::MatrixPerspective(fovY, aspect, nearPlane, farPlane));
    }

    Matrix Matrix::Ortho(double left, double right, double bottom, double top, double nearPlane, double farPlane) noexcept {
        return FromRay(::MatrixOrtho(left, right, bottom, top, nearPlane, farPlane));
    }

    // Matrix Inspection & Inverse Methods
    float Matrix::GetDeterminant() const noexcept {
        return ::MatrixDeterminant(ToRay(*this));
    }

    Matrix Matrix::GetTransposed() const noexcept {
        return FromRay(::MatrixTranspose(ToRay(*this)));
    }

    Matrix Matrix::GetInverted() const noexcept {
        return FromRay(::MatrixInvert(ToRay(*this)));
    }

    // In-place Modifier Methods
    Matrix& Matrix::ApplyTranspose() noexcept {
        *this = GetTransposed();
        return *this;
    }

    Matrix& Matrix::ApplyInvert() noexcept {
        *this = GetInverted();
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

#pragma endregion

    // --- Geometry ---
    bool Rectangle::Contains(Vector2 point) const noexcept {
        return CheckCollisionPointRec(ToRay(point), ToRay(*this));
    }

    bool Rectangle::Overlaps(Rectangle other) const noexcept {
        return CheckCollisionRecs(ToRay(*this), ToRay(other));
    }

    Rectangle Rectangle::GetCollision(Rectangle other) const noexcept {
        return FromRay(GetCollisionRec(ToRay(*this), ToRay(other)));
    }

    bool Circle::contains(const Vector2 other) const {
        return ::CheckCollisionPointCircle(ToRay(other), ToRay(this->center), this->radius);
    }

    bool Circle::overlaps(const Circle other) const {
        return ::CheckCollisionCircles(ToRay(this->center), this->radius, ToRay(other.center), other.radius);
    }

    bool Circle::overlaps(const Rectangle other) const {
        return ::CheckCollisionCircleRec(ToRay(this->center), this->radius, ToRay(other));
    }

}
