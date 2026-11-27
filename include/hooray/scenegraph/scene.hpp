#pragma once
#include <vector>
#include <hooray/platform/input.hpp>

#include "layer.hpp"
#include "node.hpp"

namespace hooray {
    class Scene : public Node {
    public:
        void add_layer(LayerUI layer) {
            layers_.emplace_back(layer);
        }

        void add_layer(Layer2D layer) {
            layers_.emplace_back(std::move(layer));
        }

    protected:
        void on_init(const AssetManager &assets) override {
            for (auto &layer: layers_) {
                std::visit([&assets](auto &l) { l.init(assets); }, layer);
            }
        }

        void on_update(float dt) override {
            if (!is_active()) return;
            for (auto &layer: layers_) {
                std::visit([dt](auto &l) {
                    if (l.is_active()) {
                        l.update(dt);
                    }
                }, layer);
            }
        }

        void on_draw(RenderCommandList &cmds) override {
            if (!is_visible()) return;
            for (auto &layer: layers_) {
                std::visit([&cmds](auto &l) {
                    if (l.is_visible()) {
                        l.draw(cmds);
                    }
                }, layer);
            }
        }

        void on_destroy() override {
            for (auto &layer: layers_) {
                std::visit([](auto &l) { l.destroy(); }, layer);
            }
        }

        void on_key_event(const KeyEvent &event) override {
            for (auto &layer: layers_) {
                std::visit([&](auto &l) { l.handle_key_event(event); }, layer);
            }
        }

        void on_mouse_event(const MouseEvent &event) override {
            for (auto &layer: layers_) {
                std::visit([&](auto &l) { l.handle_mouse_event(event); }, layer);
            }
        }

        void on_gamepad_event(const GamepadEvent &event) override {
            for (auto &layer: layers_) {
                std::visit([&](auto &l) { l.handle_gamepad_event(event); }, layer);
            }
        }

        void on_window_event(const WindowEvent &event) override {
            for (auto &layer: layers_) {
                std::visit([&](auto &l) { l.handle_window_event(event); }, layer);
            }
        }

    private:
        std::vector<Layers> layers_;
    };
}
