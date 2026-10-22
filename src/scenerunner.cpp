#include <hooray/scenerunner.hpp>
#include <iostream>
#include "raylib.h"

namespace Hooray {

    namespace {
        ::Color toRaylibColor(Color c) {
            return ::Color{c.r, c.g, c.b, c.a};
        }

        ::Camera2D toRaylibCamera2D(const Camera2D& cam) {
            return ::Camera2D{
                .offset = {cam.offset.x, cam.offset.y},
                .target = {cam.target.x, cam.target.y},
                .rotation = cam.rotation,
                .zoom = cam.zoom
            };
        }

    }

    DeclarativeApp::DeclarativeApp(AppConfig config) : m_config(std::move(config)) {}

    DeclarativeApp::~DeclarativeApp() = default;

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
            OnDraw();
            ::EndDrawing();
        }

        ::CloseWindow();

        return 1;
    }

    static void DrawRectElement(const RectangleShape &elem) {
        ::DrawRectangleRec(
            ::Rectangle{elem.position.x, elem.position.y, elem.position.x + elem.size.x, elem.position.y + elem.size.y},
            toRaylibColor(elem.fillColor)
        );
    }

    static void DrawCircleElement(const CircleShape &elem) {
        ::DrawCircleV(
            ::Vector2{.x = elem.position.x, .y = elem.position.y},
            elem.radius,
            toRaylibColor(elem.fillColor)
        );
    }

    static void DrawTriangleShape(const TriangleShape &elem) {
        const ::Vector2 v1 = {elem.position.x, elem.position.y};
        const ::Vector2 v2 = {elem.position.x - elem.size / 2.0f, elem.position.y + elem.size};
        const ::Vector2 v3 = {elem.position.x + elem.size / 2.0f, elem.position.y + elem.size};

        ::DrawTriangle(v1, v2, v3, toRaylibColor(elem.fillColor));
    }

    void DeclarativeApp::DrawElement(const VisualElement2D &elem) {
        std::visit([&]<typename T0>(const T0& c) {
            using T = std::decay_t<T0>;

            if (!c.visible) return;

            if constexpr (std::is_same_v<T, RectangleShape>) {
                DrawRectElement(c);
            } else if constexpr (std::is_same_v<T, CircleShape>) {
                DrawCircleElement(c);
            } else if constexpr (std::is_same_v<T, TriangleShape>) {
                DrawTriangleShape(c);
            } else {
                // todo: handle other element types if needed
            }
        }, elem);
    }

    void DeclarativeApp::OnDraw() {
        for (auto &scene : m_config.scenes) {
            if (!scene.visible) continue;
            for (const auto& layerVariant : scene.layers) {
                std::visit([&](const auto& sceneLayer) {
                    using T = std::decay_t<decltype(sceneLayer)>;

                    if constexpr (std::is_same_v<T, Layer2D>) {
                        if (sceneLayer.visible) {
                            ::BeginMode2D(toRaylibCamera2D(sceneLayer.camera));
                            for (const auto& elem : sceneLayer.elements) {
                                DrawElement(elem);
                            }
                            ::EndMode2D();
                        }
                    }
                }, layerVariant);
            }
        }
    }

}
