#pragma once

#include <concepts>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "node.hpp"
#include "camera.hpp"
#include "../assets/assetmanager.hpp"
#include "hooray/render/drawcommands.hpp"

namespace hooray {
    template<typename T>
    concept DerivedNode = std::derived_from<std::decay_t<T>, Node>;

    class Layer2D : public Node {
    public:
        void set_camera(Camera2D camera) {
            camera_ = std::move(camera);
        }

        [[nodiscard]] std::optional<Camera2D> get_camera() const {
            return camera_;
        }

        // 1. Construct in-place and return a typed pointer for easy user manipulation
        template<DerivedNode T, typename... Args>
        std::shared_ptr<T> add_element(Args &&... args) {
            auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
            elements_.push_back(ptr);
            return ptr;
        }

        // 2. Accept an existing rvalue/lvalue node (preserves ergonomic value-passing style)
        template<DerivedNode T>
        std::shared_ptr<std::decay_t<T> > add_element(T &&element) {
            using NodeT = std::decay_t<T>;
            auto ptr = std::make_shared<NodeT>(std::forward<T>(element));
            elements_.push_back(ptr);
            return ptr;
        }

        // 3. Accept a pre-built shared_ptr
        void add_element(std::shared_ptr<Node> element) {
            if (element) {
                elements_.push_back(std::move(element));
            }
        }

        [[nodiscard]] std::vector<std::shared_ptr<Node> > &get_elements() {
            return elements_;
        }

        [[nodiscard]] const std::vector<std::shared_ptr<Node> > &get_elements() const {
            return elements_;
        }

    protected:
        void on_init(const AssetManager &assets) override {
            for (auto &elem: elements_) {
                if (elem) elem->init(assets);
            }
        }

        void on_update(float dt) override {
            if (!is_active()) return;

            if (camera_ && camera_->is_active()) {
                camera_->update(dt);
            }

            for (auto &el: elements_) {
                if (el) el->update(dt);
            }
        }

        void on_draw(RenderCommandList &cmds) override {
            if (!is_visible()) return;
            if (camera_) {
                cmds.emplace<BeginCamera2DCmd>(BeginCamera2DCmd{
                    .offset = camera_->get_offset(),
                    .target = camera_->get_target(),
                    .rotation = camera_->get_rotation(),
                    .zoom = camera_->get_zoom()
                });
            }
            for (auto &elem: elements_) {
                if (elem) {
                    elem->draw(cmds);
                }
            }
            if (camera_) {
                cmds.emplace<EndCamera2DCmd>();
            }
        }

        void on_destroy() override {
            for (auto &elem: elements_) {
                if (elem) elem->destroy();
            }
        }

        void on_window_event(const WindowEvent &event) override {
            if (camera_) camera_->handle_window_event(event);
            for (auto &el: elements_) {
                if (el) el->handle_window_event(event);
            }
        }

    private:
        std::optional<Camera2D> camera_;
        std::vector<std::shared_ptr<Node> > elements_;
    };

    class LayerUI : public Node {
    public:
        template<DerivedNode T, typename... Args>
        std::shared_ptr<T> add_element(Args &&... args) {
            auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
            elements_.push_back(ptr);
            return ptr;
        }

        template<DerivedNode T>
        std::shared_ptr<std::decay_t<T> > add_element(T &&element) {
            using NodeT = std::decay_t<T>;
            auto ptr = std::make_shared<NodeT>(std::forward<T>(element));
            elements_.push_back(ptr);
            return ptr;
        }

        void add_element(std::shared_ptr<Node> element) {
            if (element) {
                elements_.push_back(std::move(element));
            }
        }

        [[nodiscard]] std::vector<std::shared_ptr<Node> > &get_elements() {
            return elements_;
        }

    protected:
        void on_init(const AssetManager &assets) override {
            for (auto &elem: elements_) {
                if (elem) elem->init(assets);
            }
        }

        void on_update(float dt) override {
            if (!is_active()) return;
            for (auto &elem: elements_) {
                if (elem) elem->update(dt);
            }
        }

        void on_draw(RenderCommandList &cmds) override {
            if (!is_visible()) return;
            for (auto &elem: elements_) {
                if (elem) {
                    elem->draw(cmds);
                }
            }
        }

        void on_destroy() override {
            for (auto &elem: elements_) {
                if (elem) elem->destroy();
            }
        }

        void on_window_event(const WindowEvent &event) override {
            for (auto &el: elements_) {
                if (el) el->handle_window_event(event);
            }
        }

    private:
        std::vector<std::shared_ptr<Node> > elements_;
    };

    using Layers = std::variant<LayerUI, Layer2D>;
}
