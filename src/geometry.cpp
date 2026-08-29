#include "conversion.hpp"
#include "types.hpp"
#include "raylib.h"

namespace Hooray {

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
