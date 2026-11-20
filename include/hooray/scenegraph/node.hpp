#pragma once

#include <memory>
#include <type_traits>
#include <utility>
#include "../core/controller.hpp"
#include "../core/math.hpp"

namespace hooray {
    class Node {
    public:
        virtual ~Node() = default;

        [[nodiscard]] bool is_visible() const { return visible_; }
        void set_visible(const bool visible) { visible_ = visible; }

        [[nodiscard]] bool is_active() const { return active_; }
        void set_active(const bool active) { active_ = active; }

        template<typename T>
        void set_controller(T controller) {
            controller_ = std::make_shared<std::decay_t<T> >(std::forward<T>(controller));
            controller_->on_attach(*this);
        }

        void set_controller(std::shared_ptr<IController> controller) {
            controller_ = std::move(controller);
            if (controller_) {
                controller_->on_attach(*this);
            }
        }

        [[nodiscard]] IController *get_controller() const {
            return controller_.get();
        }

        void init() {
            if (controller_) controller_->on_init(*this);
            on_init();
        }

        void update(float dt) {
            if (!active_) return;
            if (controller_) controller_->on_update(*this, dt);
            on_update(dt);
        }

        void draw() {
            if (!visible_) return;
            on_draw();
            if (controller_) {
                controller_->on_draw(*this);
            }
        }

        void handle_window_event(WindowEvent event) {
            if (controller_) controller_->on_window_event(*this, event);
            on_window_event(event);
        }

        void destroy() {
            if (controller_) controller_->on_destroy(*this);
            on_destroy();
        }

    protected:
        bool active_{true};
        bool visible_{true};

        virtual void on_init() {
        }

        virtual void on_update(float dt) {
        }

        virtual void on_draw() {
        }

        virtual void on_destroy() {
        }

        virtual void on_window_event(const WindowEvent &event) {
        }

        std::shared_ptr<IController> controller_{nullptr};
    };

    class Node2D : public Node {
    public:
        ~Node2D() override = default;

        void set_transform(const Transform2D &t) { transform = t; }
        [[nodiscard]] Transform2D get_transform() const { return transform; }
        Transform2D transform{};
    };
} // namespace hooray
