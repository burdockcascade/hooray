#pragma once
#include <raylib.h>

namespace hooray {

    inline ::Color to_raylib_color(Color c) {
        return ::Color{.r = c.r, .g = c.g, .b = c.b, .a = c.a};
    }

}
