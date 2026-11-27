#pragma once
#include "../platform/window.hpp"
#include "hooray/render/drawcommands.hpp"
#include "hooray/platform/input.hpp"

namespace hooray {
    class Node;

    class IController {
    public:
        virtual ~IController() = default;

        // Lifecycle
        virtual void on_attach(Node& node) {}
        virtual void on_init(Node& node) {}
        virtual void on_update(Node& node, float dt) {}
        virtual void on_draw(Node& node, RenderCommandList& cmds) {}
        virtual void on_destroy(Node& node) {}
        virtual void on_window_event(Node& node, WindowEvent& event) {}
        virtual void on_key_event(Node& node, KeyEvent& event) {}
        virtual void on_mouse_event(Node& node, MouseEvent& event) {}
        virtual void on_gamepad_event(Node& node, GamepadEvent& event) {}

    };

    template <typename NodeType>
    class Controller : public IController {
    public:
        ~Controller() override = default;

        // Typed Lifecycle
        virtual void on_attach(NodeType& node) {}
        virtual void on_init(NodeType& node) {}
        virtual void on_update(NodeType& node, float dt) {}
        virtual void on_draw(NodeType& node, RenderCommandList& cmds) {}
        virtual void on_destroy(NodeType& node) {}
        virtual void on_window_event(NodeType& node, WindowEvent& event) {}
        virtual void on_key_event(NodeType& node, KeyEvent& event) {}
        virtual void on_mouse_event(NodeType& node, MouseEvent& event) {}
        virtual void on_gamepad_event(NodeType& node, GamepadEvent& event) {}

        // IController forwards
        void on_attach(Node& n) override { on_attach(static_cast<NodeType&>(n)); }
        void on_init(Node& n) override { on_init(static_cast<NodeType&>(n)); }
        void on_update(Node& n, const float dt) override { on_update(static_cast<NodeType&>(n), dt); }
        void on_draw(Node& n, RenderCommandList& cmds) override { on_draw(static_cast<NodeType&>(n), cmds); }
        void on_destroy(Node& n) override { on_destroy(static_cast<NodeType&>(n)); }
        void on_window_event(Node& n, WindowEvent& event) override { on_window_event(static_cast<NodeType&>(n), event); }
        void on_key_event(Node& n, KeyEvent& event) override { on_key_event(static_cast<NodeType&>(n), event); }
        void on_mouse_event(Node& n, MouseEvent& event) override { on_mouse_event(static_cast<NodeType&>(n), event); }
        void on_gamepad_event(Node& n, GamepadEvent& event) override { on_gamepad_event(static_cast<NodeType&>(n), event); }
    };

}
