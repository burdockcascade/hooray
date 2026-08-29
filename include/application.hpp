#pragma once
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "commands.hpp"

namespace Hooray {

    class Layer2d {
    public:
        explicit Layer2d(std::vector<Command>& command_queue): command_queue_(command_queue) {}

        void drawLine(Vector2 start, Vector2 end, float thickness, Color color) const;
        void drawCircle(Vector2 center, float radius, Color color) const;
        void drawRectangle(Rectangle rect, Color color) const;

    private:
        std::vector<Command>& command_queue_;
    };

    class Render {
    public:
        explicit Render(std::vector<Command>& command_queue): command_queue_(command_queue) {}

        void drawFPS(Vector2 position) const {
            command_queue_.emplace_back(DrawFPSCmd{position});
        }

        void clearBackground(Color color) const;

        template <typename Func>
        void withLayer2d(const Camera2D &camera2d, Func&& func) const {
            command_queue_.emplace_back(BeginMode2DCmd{camera2d});
            func(Layer2d(command_queue_));
            command_queue_.emplace_back(EndMode2DCmd{});
        }

    private:
        std::vector<Command>& command_queue_;
    };

    class Application {
    public:
        Application(const int width, const int height, std::string  title) : width_(width), height_(height), title_(std::move(title)) {}

        virtual ~Application() = default;

        virtual void on_init() {}
        virtual void on_update(float delta_time) {}
        virtual void on_draw(Render render) {}

        virtual void on_key_pressed(int key) {}
        virtual void on_mouse_moved(Vector2 vector2) {}

        virtual void on_mouse_pressed(int button, Vector2 vector2) {}
        virtual void on_mouse_released(int button, Vector2 vector2) {}

        void execute_commands() const;

        void run();

    private:
        int width_;
        int height_;
        std::string title_;
        bool is_running_{ true };
        std::vector<Command> command_queue_{1024};

    };

} // namespace Hooray