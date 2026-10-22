#include <hooray/scenerunner.hpp>
#include <iostream>
#include "raylib.h"

namespace Hooray {

    namespace {
        ::Color toRaylibColor(Color c) {
            return ::Color{c.r, c.g, c.b, c.a};
        }

    }

    void DeclarativeApp::quit() {
        m_running = false;
    }

    int DeclarativeApp::run() {
        if (m_config.window.resizable) {
            ::SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        }

        ::InitWindow(m_config.window.width, m_config.window.height, m_config.window.title.c_str());
        ::SetTargetFPS(m_config.window.targetFps);

        m_running = true;

        while (m_running && !::WindowShouldClose()) {

            if (m_config.window.showFPS) {
                ::DrawFPS(10, 10);
            }

            const float dt = ::GetFrameTime();

            ::BeginDrawing();
            ::ClearBackground(toRaylibColor(m_config.window.bgColor));
            ::EndDrawing();
        }

        ::CloseWindow();

        return 1;
    }

    DeclarativeApp::DeclarativeApp(AppConfig config) : m_config(std::move(config)) {}

    DeclarativeApp::~DeclarativeApp() = default;

}
