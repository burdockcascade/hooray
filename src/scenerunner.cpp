#include <hooray/scenerunner.hpp>
#include <iostream>
#include "raylib.h"

namespace Hooray {

    namespace {
        ::Color ToRaylibColor(Color c) {
            return ::Color{.r = c.r, .g = c.g, .b = c.b, .a = c.a};
        }

        ::Camera2D ToRaylibCamera2D(const Camera2D& cam) {
            return ::Camera2D{
                .offset = {.x = cam.offset.x, .y = cam.offset.y},
                .target = {.x = cam.target.x, .y = cam.target.y},
                .rotation = cam.rotation,
                .zoom = cam.zoom
            };
        }

        template <typename T>
        void ProcessInit(T& node) {
            if constexpr (requires { node.controller; }) {
                std::visit([&](auto& ctrl) {
                    using SlotType = std::decay_t<decltype(ctrl)>;
                    if constexpr (std::is_same_v<SlotType, NodeCallbacks<T>>) {
                        if (ctrl.onInit) ctrl.onInit(node);
                    } else if constexpr (std::is_same_v<SlotType, std::shared_ptr<NodeController<T>>>) {
                        if (ctrl) ctrl->OnInit(node);
                    }
                }, node.controller);
            }
        }

        template <typename T>
        void ProcessUpdate(float dt, T& node) {
            if constexpr (requires { node.controller; }) {
                std::visit([&](auto& ctrl) {
                    using SlotType = std::decay_t<decltype(ctrl)>;
                    if constexpr (std::is_same_v<SlotType, NodeCallbacks<T>>) {
                        if (ctrl.onUpdate) ctrl.onUpdate(dt, node);
                    } else if constexpr (std::is_same_v<SlotType, std::shared_ptr<NodeController<T>>>) {
                        if (ctrl) ctrl->OnUpdate(dt, node);
                    }
                }, node.controller);
            }
        }

        template <typename T>
        void ProcessDestroy(float dt, T& node) {
            if constexpr (requires { node.controller; }) {
                std::visit([&](auto& ctrl) {
                    using SlotType = std::decay_t<decltype(ctrl)>;
                    if constexpr (std::is_same_v<SlotType, NodeCallbacks<T>>) {
                        if (ctrl.onDestroy) ctrl.onDestroy(node);
                    } else if constexpr (std::is_same_v<SlotType, std::shared_ptr<NodeController<T>>>) {
                        if (ctrl) ctrl->OnDestroy(dt, node);
                    }
                }, node.controller);
            }
        }

        void ForEachActiveElement(std::vector<Scene>& scenes, auto&& fn) {
            for (auto& scene : scenes) {
                if (!scene.active) continue;
                for (auto& layerVariant : scene.layers) {
                    std::visit([&](auto& layer) {
                        using L = std::decay_t<decltype(layer)>;
                        if constexpr (std::is_same_v<L, Layer2D>) {
                            if (!layer.active) return;
                            for (auto& elem : layer.elements) {
                                std::visit(fn, elem);
                            }
                        } else {
                            // Handle other layer types if needed
                        }
                    }, layerVariant);
                }
            }
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

        // Initialize all controllers
        ForEachActiveElement(m_config.scenes, [](auto& elem) {
            ProcessInit(elem);
        });

        // Main Game Loop
        while (m_running && !::WindowShouldClose()) {
            const float dt = ::GetFrameTime();

            // Update controllers
            ForEachActiveElement(m_config.scenes, [dt](auto& elem) {
                ProcessUpdate(dt, elem);
            });

            ::BeginDrawing();
            ::ClearBackground(ToRaylibColor(m_config.window.bgColor));

            if (m_config.window.showFPS) {
                ::DrawFPS(10, 10);
            }

            OnDraw();
            ::EndDrawing();
        }

        // Cleanup controllers
        const float lastDt = ::GetFrameTime();
        ForEachActiveElement(m_config.scenes, [lastDt](auto& elem) {
            ProcessDestroy(lastDt, elem);
        });

        ::CloseWindow();
        return 0;
    }

    static void DrawRectElement(const RectangleShape &elem) {
        ::DrawRectangleRec(
            ::Rectangle{elem.position.x, elem.position.y, elem.size.x, elem.size.y},
            ToRaylibColor(elem.fillColor)
        );
    }

    static void DrawCircleElement(const CircleShape &elem) {
        ::DrawCircleV(
            ::Vector2{.x = elem.position.x, .y = elem.position.y},
            elem.radius,
            ToRaylibColor(elem.fillColor)
        );
    }

    static void DrawTriangleShape(const TriangleShape &elem) {
        const ::Vector2 v1 = {elem.position.x, elem.position.y};
        const ::Vector2 v2 = {elem.position.x - elem.size / 2.0f, elem.position.y + elem.size};
        const ::Vector2 v3 = {elem.position.x + elem.size / 2.0f, elem.position.y + elem.size};

        ::DrawTriangle(v1, v2, v3, ToRaylibColor(elem.fillColor));
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
            }
        }, elem);
    }

    void DeclarativeApp::OnDraw() {
        for (auto &scene : m_config.scenes) {
            if (!scene.visible) continue;
            for (const auto& layerVariant : scene.layers) {
                std::visit([&](const auto& layer) {
                    if (!layer.visible) return;
                    using T = std::decay_t<decltype(layer)>;
                    if constexpr (std::is_same_v<T, Layer2D>) {
                        ::BeginMode2D(ToRaylibCamera2D(layer.camera));
                        for (const auto& elem : layer.elements) {
                            DrawElement(elem);
                        }
                        ::EndMode2D();
                    }
                }, layerVariant);
            }
        }
    }

}