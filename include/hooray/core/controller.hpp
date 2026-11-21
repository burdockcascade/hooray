#pragma once
#include "../platform/window.hpp"
#include "hooray/render/drawcommands.hpp"

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

        // IController forwards
        void on_attach(Node& n) override { on_attach(static_cast<NodeType&>(n)); }
        void on_init(Node& n) override { on_init(static_cast<NodeType&>(n)); }
        void on_update(Node& n, const float dt) override { on_update(static_cast<NodeType&>(n), dt); }
        void on_draw(Node& n, RenderCommandList& cmds) override { on_draw(static_cast<NodeType&>(n)); }
        void on_destroy(Node& n) override { on_destroy(static_cast<NodeType&>(n)); }
        void on_window_event(Node& n, WindowEvent& event) override { on_window_event(static_cast<NodeType&>(n), event); }
    };

}
