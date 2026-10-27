#pragma once
#include <functional>
#include <memory>
#include <variant>

#include "input.hpp"

namespace Hooray {

    template <typename T>
    struct NodeController {
        virtual ~NodeController() = default;

        // Lifecycle
        virtual void OnInit(T& node) {};
        virtual void OnUpdate(float dt, T& node) {};
        virtual void OnDestroy(float dt, T& node) { };

        virtual void OnKeyEvent(const KeyEvent& event, T& node) {}
        virtual void OnMouseEvent(const MouseEvent& event, T& node) {}

    };

    template <typename T>
    struct NodeCallbacks {
        std::function<void(T& node)> onInit{nullptr};
        std::function<void(float dt, T& node)> onUpdate{nullptr};
        std::function<void(T& node)> onDestroy{nullptr};
        std::function<void(const KeyEvent& event, T& node)> onKeyEvent{nullptr};
        std::function<void(const MouseEvent& event, T& node)> onMouseEvent{nullptr};
    };

    template <typename T>
    using ControllerSlot = std::variant<
        std::monostate,                         // empty / no controller
        NodeCallbacks<T>,                       // lightweight callbacks
        std::shared_ptr<NodeController<T>> // class-based controller      // class-based controller
    >;

}
