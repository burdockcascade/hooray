#pragma once
#include <ostream>
#include <string_view>

namespace hooray {

    enum class WindowAction {
        RESIZED,
        FOCUS_GAINED,
        FOCUS_LOST,
        MINIMIZED,
        MAXIMIZED,
        UNMAXIMIZED,
        RESTORED,
        MOVED,
    };

    constexpr std::string_view to_string(WindowAction action) noexcept {
        switch (action) {
            case WindowAction::RESIZED:      return "RESIZED";
            case WindowAction::FOCUS_GAINED: return "FOCUS_GAINED";
            case WindowAction::FOCUS_LOST:   return "FOCUS_LOST";
            case WindowAction::MINIMIZED:    return "MINIMIZED";
            case WindowAction::MAXIMIZED:    return "MAXIMIZED";
            case WindowAction::UNMAXIMIZED:  return "UNMAXIMIZED";
            case WindowAction::RESTORED:     return "RESTORED";
            case WindowAction::MOVED:        return "MOVED";
        }
        return "UNKNOWN";
    }

    inline std::ostream& operator<<(std::ostream& os, WindowAction action) {
        return os << to_string(action);
    }

    struct WindowEvent {
        WindowAction action{WindowAction::RESIZED};
        int width{0};   // New width of the window (only valid for RESIZED)
        int height{0};  // New height of the window (only valid for RESIZED)
        int pos_x{0};
        int pos_y{0};
    };

    enum class WindowFlags : uint32_t {
        NONE        = 0,
        RESIZABLE   = 1 << 0,
        FULLSCREEN  = 1 << 1,
        UNDECORATED = 1 << 2,
        VSYNC       = 1 << 3,
        HIGH_DPI    = 1 << 4,
        TRANSPARENT = 1 << 5,
        ALWAYS_ON_TOP = 1 << 6,
        HIDDEN      = 1 << 7,
        MAXIMIZED   = 1 << 8,
        MSAA_4X     = 1 << 9
    };

    constexpr WindowFlags operator|(WindowFlags lhs, WindowFlags rhs) noexcept {
        return static_cast<WindowFlags>(
            static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs)
        );
    }

    constexpr WindowFlags operator&(WindowFlags lhs, WindowFlags rhs) noexcept {
        return static_cast<WindowFlags>(
            static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs)
        );
    }

    constexpr WindowFlags& operator|=(WindowFlags& lhs, WindowFlags rhs) noexcept {
        lhs = lhs | rhs;
        return lhs;
    }

    constexpr bool has_flag(WindowFlags flags, WindowFlags check) noexcept {
        return (static_cast<uint32_t>(flags) & static_cast<uint32_t>(check)) != 0;
    }

}