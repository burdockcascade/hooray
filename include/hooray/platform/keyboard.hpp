#pragma once

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

}
