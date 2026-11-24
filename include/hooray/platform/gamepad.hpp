#pragma once

namespace hooray {

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