#pragma once
#include <ostream>
#include <string_view>
#include "../core/math.hpp"

namespace hooray {

    enum class MouseAction {
        PRESSED,   // Triggered once when first pressed
        DOWN,      // Triggered every frame while held down
        RELEASED,  // Triggered once when released
        MOVED,     // Mouse cursor moved
        SCROLLED   // Mouse wheel scrolled
    };

    constexpr std::string_view to_string(MouseAction action) noexcept {
        switch (action) {
            case MouseAction::PRESSED:  return "PRESSED";
            case MouseAction::DOWN:     return "DOWN";
            case MouseAction::RELEASED: return "RELEASED";
            case MouseAction::MOVED:    return "MOVED";
            case MouseAction::SCROLLED: return "SCROLLED";
            default:                    return "UNKNOWN";
        }
    }

    inline std::ostream& operator<<(std::ostream& os, MouseAction action) noexcept {
        return os << to_string(action);
    }

    enum class MouseButton {
        NONE = -1,
        LEFT = 0,
        RIGHT = 1,
        MIDDLE = 2,
        SIDE = 3,
        EXTRA = 4,
        FORWARD = 5,
        BACK = 6
    };

    struct MouseEvent {
        MouseAction action{MouseAction::MOVED};
        MouseButton button{MouseButton::NONE};
        Vector2 position{.x = 0.0f, .y = 0.0f};      // Current screen coordinates
        Vector2 delta{.x = 0.0f, .y = 0.0f};         // Position movement delta
        Vector2 scroll{.x = 0.0f, .y = 0.0f};        // Scroll wheel delta (x: h-scroll, y: v-scroll)
    };

}
