#pragma once
#include "hooray/core/math.hpp"

namespace hooray {

    enum class KeyAction {
        PRESSED,   // Triggered once when first pressed
        DOWN,      // Triggered every frame while held down
        RELEASED   // Triggered once when released
    };

    enum class Key {
        UNKNOWN,

        // Printable / ASCII matching
        SPACE,
        APOSTROPHE,
        COMMA,
        MINUS,
        PERIOD,
        SLASH,
        ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
        SEMICOLON,
        EQUAL,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        LEFT_BRACKET,
        BACKSLASH,
        RIGHT_BRACKET,
        GRAVE,

        // Function keys (Raylib / GLFW values starting at 256)
        ESCAPE,
        ENTER,
        TAB,
        BACKSPACE,
        INSERT,
        DELETE,
        RIGHT,
        LEFT,
        DOWN,
        UP,
        PAGEUP,
        PAGEDOWN,
        HOME,
        END,
        CAPSLOCK,
        SCROLL_LOCK,
        NUM_LOCK,
        PRINT_SCREEN,
        PAUSE,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        // Keypad keys
        KP0, KP1, KP2, KP3, KP4, KP5, KP6, KP7, KP8, KP9,
        KP_DECIMAL,
        KP_DIVIDE,
        KP_MULTIPLY,
        KP_SUBTRACT,
        KP_ADD,
        KP_ENTER,
        KP_EQUAL,

        // Modifiers & System
        LEFTSHIFT,
        LEFT_CONTROL,
        LEFT_ALT,
        LEFT_SUPER,
        RIGHTSHIFT,
        RIGHT_CONTROL,
        RIGHT_ALT,
        RIGHT_SUPER,
        MENU
    };

    struct KeyEvent {
        Key key{Key::UNKNOWN};
        KeyAction action{KeyAction::PRESSED};
    };

    enum class MouseAction {
        PRESSED,   // Triggered once when first pressed
        DOWN,      // Triggered every frame while held down
        RELEASED,  // Triggered once when released
        MOVED,     // Mouse cursor moved
        SCROLLED   // Mouse wheel scrolled
    };

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

    enum class GamepadAction {
        CONNECTED,     // Triggered once when gamepad is connected
        DISCONNECTED,  // Triggered once when gamepad is disconnected
        PRESSED,       // Triggered once when button is first pressed
        DOWN,          // Triggered every frame while button is held down
        RELEASED,      // Triggered once when button is released
        AXIS_MOVED     // Triggered when an analog axis is outside deadzone or changes
    };

    enum class GamepadButton {
        UNKNOWN = 0,
        // D-Pad (Left Face)
        DPAD_UP,
        DPAD_RIGHT,
        DPAD_DOWN,
        DPAD_LEFT,
        // Face Buttons (Right Face: Xbox Y/B/A/X, PS Triangle/Circle/Cross/Square)
        FACE_UP,
        FACE_RIGHT,
        FACE_DOWN,
        FACE_LEFT,
        // Triggers & Bumpers
        LEFT_BUMPER,
        LEFT_TRIGGER,
        RIGHT_BUMPER,
        RIGHT_TRIGGER,
        // Center Buttons (Select/Back, Guide/Home, Start/Options)
        MIDDLE_LEFT,
        MIDDLE,
        MIDDLE_RIGHT,
        // Thumbstick Clicks (L3 / R3)
        LEFT_THUMB,
        RIGHT_THUMB
    };

    enum class GamepadAxis {
        NONE = -1,
        LEFT_X = 0,
        LEFT_Y = 1,
        RIGHT_X = 2,
        RIGHT_Y = 3,
        LEFT_TRIGGER = 4,
        RIGHT_TRIGGER = 5
    };

    struct GamepadEvent {
        int gamepad_id{0};
        GamepadAction action{GamepadAction::PRESSED};
        GamepadButton button{GamepadButton::UNKNOWN};
        GamepadAxis axis{GamepadAxis::NONE};
        float axis_value{0.0f};      // Normalized range: [-1.0f, 1.0f] for sticks, [-1.0f, 1.0f] or [0.0f, 1.0f] for triggers
        float axis_delta{0.0f};      // Change since previous frame
    };

}
