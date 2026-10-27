#pragma once
#include "math.hpp"

namespace Hooray {

    enum class KeyAction {
        Pressed,   // Triggered once when first pressed
        Down,      // Triggered every frame while held down
        Released   // Triggered once when released
    };

    enum class Key {
        Unknown,

        // Printable / ASCII matching
        Space,
        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,
        Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
        Semicolon,
        Equal,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        LeftBracket,
        Backslash,
        RightBracket,
        Grave,

        // Function keys (Raylib / GLFW values starting at 256)
        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        // Keypad keys
        Kp0, Kp1, Kp2, Kp3, Kp4, Kp5, Kp6, Kp7, Kp8, Kp9,
        KpDecimal,
        KpDivide,
        KpMultiply,
        KpSubtract,
        KpAdd,
        KpEnter,
        KpEqual,

        // Modifiers & System
        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu
    };

    struct KeyEvent {
        Key key{Key::Unknown};
        KeyAction action{KeyAction::Pressed};
    };

    enum class MouseAction {
        Pressed,   // Triggered once when first pressed
        Down,      // Triggered every frame while held down
        Released,  // Triggered once when released
        Moved,     // Mouse cursor moved
        Scrolled   // Mouse wheel scrolled
    };

    enum class MouseButton {
        None = -1,
        Left = 0,
        Right = 1,
        Middle = 2,
        Side = 3,
        Extra = 4,
        Forward = 5,
        Back = 6
    };

    struct MouseEvent {
        MouseAction action{MouseAction::Moved};
        MouseButton button{MouseButton::None};
        Vector2 position{.x = 0.0f, .y = 0.0f};      // Current screen coordinates
        Vector2 delta{.x = 0.0f, .y = 0.0f};         // Position movement delta
        Vector2 scroll{.x = 0.0f, .y = 0.0f};        // Scroll wheel delta (x: h-scroll, y: v-scroll)
    };

}
