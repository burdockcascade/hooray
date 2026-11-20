#pragma once
#include <ostream>
#include <string_view>

namespace hooray {

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