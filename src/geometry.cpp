#include <raylib.h>
#include <hooray/math.hpp>
#include <hooray/geometry.hpp>
#include "conversion.hpp"

namespace Hooray {

    bool Rectangle::contains(Vector2 point) const noexcept {
        return CheckCollisionPointRec(ToRay(point), ToRay(*this));
    }

    bool Rectangle::overlaps(Rectangle other) const noexcept {
        return CheckCollisionRecs(ToRay(*this), ToRay(other));
    }

    Rectangle Rectangle::get_collision(Rectangle other) const noexcept {
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