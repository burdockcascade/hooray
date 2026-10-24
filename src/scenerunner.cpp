#include <hooray/scenerunner.hpp>
#include <iostream>
#include "raylib.h"
#include "rlgl.h"

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

#pragma region Keyboard

        int HoorayKeyToRaylib(Key key) {
            switch (key) {
                // Control & Whitespace
                case Key::Space:            return ::KEY_SPACE;
                case Key::Escape:           return ::KEY_ESCAPE;
                case Key::Enter:            return ::KEY_ENTER;
                case Key::Tab:              return ::KEY_TAB;
                case Key::Backspace:        return ::KEY_BACKSPACE;
                case Key::Insert:           return ::KEY_INSERT;
                case Key::Delete:           return ::KEY_DELETE;

                // Navigation
                case Key::Right:            return ::KEY_RIGHT;
                case Key::Left:             return ::KEY_LEFT;
                case Key::Down:             return ::KEY_DOWN;
                case Key::Up:               return ::KEY_UP;
                case Key::PageUp:           return ::KEY_PAGE_UP;
                case Key::PageDown:         return ::KEY_PAGE_DOWN;
                case Key::Home:             return ::KEY_HOME;
                case Key::End:              return ::KEY_END;

                // Locks
                case Key::CapsLock:         return ::KEY_CAPS_LOCK;
                case Key::ScrollLock:       return ::KEY_SCROLL_LOCK;
                case Key::NumLock:          return ::KEY_NUM_LOCK;
                case Key::PrintScreen:      return ::KEY_PRINT_SCREEN;
                case Key::Pause:            return ::KEY_PAUSE;

                // Number Keys (Top Row)
                case Key::Zero:             return ::KEY_ZERO;
                case Key::One:              return ::KEY_ONE;
                case Key::Two:              return ::KEY_TWO;
                case Key::Three:            return ::KEY_THREE;
                case Key::Four:             return ::KEY_FOUR;
                case Key::Five:             return ::KEY_FIVE;
                case Key::Six:              return ::KEY_SIX;
                case Key::Seven:            return ::KEY_SEVEN;
                case Key::Eight:            return ::KEY_EIGHT;
                case Key::Nine:             return ::KEY_NINE;

                // Alphabet Keys
                case Key::A:                return ::KEY_A;
                case Key::B:                return ::KEY_B;
                case Key::C:                return ::KEY_C;
                case Key::D:                return ::KEY_D;
                case Key::E:                return ::KEY_E;
                case Key::F:                return ::KEY_F;
                case Key::G:                return ::KEY_G;
                case Key::H:                return ::KEY_H;
                case Key::I:                return ::KEY_I;
                case Key::J:                return ::KEY_J;
                case Key::K:                return ::KEY_K;
                case Key::L:                return ::KEY_L;
                case Key::M:                return ::KEY_M;
                case Key::N:                return ::KEY_N;
                case Key::O:                return ::KEY_O;
                case Key::P:                return ::KEY_P;
                case Key::Q:                return ::KEY_Q;
                case Key::R:                return ::KEY_R;
                case Key::S:                return ::KEY_S;
                case Key::T:                return ::KEY_T;
                case Key::U:                return ::KEY_U;
                case Key::V:                return ::KEY_V;
                case Key::W:                return ::KEY_W;
                case Key::X:                return ::KEY_X;
                case Key::Y:                return ::KEY_Y;
                case Key::Z:                return ::KEY_Z;

                // Function Keys
                case Key::F1:               return ::KEY_F1;
                case Key::F2:               return ::KEY_F2;
                case Key::F3:               return ::KEY_F3;
                case Key::F4:               return ::KEY_F4;
                case Key::F5:               return ::KEY_F5;
                case Key::F6:               return ::KEY_F6;
                case Key::F7:               return ::KEY_F7;
                case Key::F8:               return ::KEY_F8;
                case Key::F9:               return ::KEY_F9;
                case Key::F10:              return ::KEY_F10;
                case Key::F11:              return ::KEY_F11;
                case Key::F12:              return ::KEY_F12;

                // Modifiers
                case Key::LeftShift:        return ::KEY_LEFT_SHIFT;
                case Key::LeftControl:      return ::KEY_LEFT_CONTROL;
                case Key::LeftAlt:          return ::KEY_LEFT_ALT;
                case Key::LeftSuper:        return ::KEY_LEFT_SUPER;
                case Key::RightShift:       return ::KEY_RIGHT_SHIFT;
                case Key::RightControl:     return ::KEY_RIGHT_CONTROL;
                case Key::RightAlt:         return ::KEY_RIGHT_ALT;
                case Key::RightSuper:       return ::KEY_RIGHT_SUPER;
                case Key::Menu:             return ::KEY_KB_MENU;

                // Punctuation & Symbols
                case Key::Apostrophe:       return ::KEY_APOSTROPHE;
                case Key::Comma:            return ::KEY_COMMA;
                case Key::Minus:            return ::KEY_MINUS;
                case Key::Period:           return ::KEY_PERIOD;
                case Key::Slash:            return ::KEY_SLASH;
                case Key::Semicolon:        return ::KEY_SEMICOLON;
                case Key::Equal:            return ::KEY_EQUAL;
                case Key::LeftBracket:      return ::KEY_LEFT_BRACKET;
                case Key::Backslash:        return ::KEY_BACKSLASH;
                case Key::RightBracket:     return ::KEY_RIGHT_BRACKET;
                case Key::Grave:            return ::KEY_GRAVE;

                // Keypad Keys
                case Key::Kp0:              return ::KEY_KP_0;
                case Key::Kp1:              return ::KEY_KP_1;
                case Key::Kp2:              return ::KEY_KP_2;
                case Key::Kp3:              return ::KEY_KP_3;
                case Key::Kp4:              return ::KEY_KP_4;
                case Key::Kp5:              return ::KEY_KP_5;
                case Key::Kp6:              return ::KEY_KP_6;
                case Key::Kp7:              return ::KEY_KP_7;
                case Key::Kp8:              return ::KEY_KP_8;
                case Key::Kp9:              return ::KEY_KP_9;
                case Key::KpDecimal:        return ::KEY_KP_DECIMAL;
                case Key::KpDivide:         return ::KEY_KP_DIVIDE;
                case Key::KpMultiply:       return ::KEY_KP_MULTIPLY;
                case Key::KpSubtract:       return ::KEY_KP_SUBTRACT;
                case Key::KpAdd:            return ::KEY_KP_ADD;
                case Key::KpEnter:          return ::KEY_KP_ENTER;
                case Key::KpEqual:          return ::KEY_KP_EQUAL;

                default:                    return ::KEY_NULL;
            }
        }

        inline constexpr Key TrackedKeys[] = {
            // Control & Whitespace
            Key::Space,
            Key::Escape,
            Key::Enter,
            Key::Tab,
            Key::Backspace,
            Key::Insert,
            Key::Delete,

            // Navigation
            Key::Right,
            Key::Left,
            Key::Down,
            Key::Up,
            Key::PageUp,
            Key::PageDown,
            Key::Home,
            Key::End,

            // Locks
            Key::CapsLock,
            Key::ScrollLock,
            Key::NumLock,
            Key::PrintScreen,
            Key::Pause,

            // Number Keys
            Key::Zero,
            Key::One,
            Key::Two,
            Key::Three,
            Key::Four,
            Key::Five,
            Key::Six,
            Key::Seven,
            Key::Eight,
            Key::Nine,

            // Alphabet Keys
            Key::A,
            Key::B,
            Key::C,
            Key::D,
            Key::E,
            Key::F,
            Key::G,
            Key::H,
            Key::I,
            Key::J,
            Key::K,
            Key::L,
            Key::M,
            Key::N,
            Key::O,
            Key::P,
            Key::Q,
            Key::R,
            Key::S,
            Key::T,
            Key::U,
            Key::V,
            Key::W,
            Key::X,
            Key::Y,
            Key::Z,

            // Function Keys
            Key::F1,
            Key::F2,
            Key::F3,
            Key::F4,
            Key::F5,
            Key::F6,
            Key::F7,
            Key::F8,
            Key::F9,
            Key::F10,
            Key::F11,
            Key::F12,

            // Modifiers
            Key::LeftShift,
            Key::LeftControl,
            Key::LeftAlt,
            Key::LeftSuper,
            Key::RightShift,
            Key::RightControl,
            Key::RightAlt,
            Key::RightSuper,
            Key::Menu,

            // Punctuation & Symbols
            Key::Apostrophe,
            Key::Comma,
            Key::Minus,
            Key::Period,
            Key::Slash,
            Key::Semicolon,
            Key::Equal,
            Key::LeftBracket,
            Key::Backslash,
            Key::RightBracket,
            Key::Grave,

            // Keypad Keys
            Key::Kp0,
            Key::Kp1,
            Key::Kp2,
            Key::Kp3,
            Key::Kp4,
            Key::Kp5,
            Key::Kp6,
            Key::Kp7,
            Key::Kp8,
            Key::Kp9,
            Key::KpDecimal,
            Key::KpDivide,
            Key::KpMultiply,
            Key::KpSubtract,
            Key::KpAdd,
            Key::KpEnter,
            Key::KpEqual
        };

#pragma endregion

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

        template <typename Fn>
        void TraverseElement(VisualElement2D& elem, Fn&& fn) {
            std::visit([&](auto& node) {
                using T = std::decay_t<decltype(node)>;
                if (!node.active) return;

                fn(node);

                if constexpr (std::is_same_v<T, Group>) {
                    for (auto& child : node.elements) {
                        TraverseElement(child, fn);
                    }
                }
            }, elem);
        }

        void ForEachActiveElement(std::vector<Scene>& scenes, auto&& fn) {
            for (auto& scene : scenes) {
                if (!scene.active) continue;
                for (auto& layerVariant : scene.layers) {
                    std::visit([&](auto& layer) {
                        using L = std::decay_t<decltype(layer)>;

                        if constexpr (std::is_same_v<L, Layer2D>) {
                            if (!layer.active) return;

                            if (layer.camera.active) {
                                fn(layer.camera);
                            }

                            for (auto& elem : layer.elements) {
                                TraverseElement(elem, fn);
                            }
                        } else if constexpr (std::is_same_v<L, LayerUI>) {
                            if (!layer.active) return;
                            for (auto& elem : layer.elements) {
                                TraverseElement(elem, fn);
                            }
                        }
                    }, layerVariant);
                }
            }
        }

        template <typename T>
        void ProcessKeyEvent(const KeyEvent& event, T& node) {
            if constexpr (requires { node.controller; }) {
                std::visit([&](auto& ctrl) {
                    using SlotType = std::decay_t<decltype(ctrl)>;
                    if constexpr (std::is_same_v<SlotType, NodeCallbacks<T>>) {
                        if (ctrl.onKeyEvent) ctrl.onKeyEvent(event, node);
                    } else if constexpr (std::is_same_v<SlotType, std::shared_ptr<NodeController<T>>>) {
                        if (ctrl) ctrl->OnKeyEvent(event, node);
                    }
                }, node.controller);
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

            for (Key key : TrackedKeys) {
                const int rk = HoorayKeyToRaylib(key);

                if (::IsKeyPressed(rk)) {
                    ForEachActiveElement(m_config.scenes, [key](auto& elem) {
                        ProcessKeyEvent({.key = key, .action = KeyAction::Pressed}, elem);
                    });
                }

                if (::IsKeyDown(rk)) {
                    ForEachActiveElement(m_config.scenes, [key](auto& elem) {
                        ProcessKeyEvent({.key = key, .action = KeyAction::Down}, elem);
                    });
                }

                if (::IsKeyReleased(rk)) {
                    ForEachActiveElement(m_config.scenes, [key](auto& elem) {
                        ProcessKeyEvent({.key = key, .action = KeyAction::Released}, elem);
                    });
                }
            }

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
        const float w = elem.size.x * elem.transform.scale.x;
        const float h = elem.size.y * elem.transform.scale.y;

        ::rlPushMatrix();
        ::rlTranslatef(elem.transform.position.x, elem.transform.position.y, 0.0f);
        ::rlRotatef(elem.transform.rotation, 0.0f, 0.0f, 1.0f);

        // Draw around origin point
        const ::Rectangle rect = { .x = -w * elem.transform.origin.x, .y = -h * elem.transform.origin.y, .width = w, .height = h };
        ::DrawRectangleRec(rect, ToRaylibColor(elem.fillColor));
        ::rlPopMatrix();
    }

    static void DrawCircleElement(const CircleShape &elem) {
        ::rlPushMatrix();
        ::rlTranslatef(elem.transform.position.x, elem.transform.position.y, 0.0f);
        ::rlRotatef(elem.transform.rotation, 0.0f, 0.0f, 1.0f);
        ::rlScalef(elem.transform.scale.x, elem.transform.scale.y, 1.0f);

        ::DrawCircleV({.x = 0.0f, .y = 0.0f}, elem.radius, ToRaylibColor(elem.fillColor));
        ::rlPopMatrix();
    }

    static void DrawTriangleShape(const TriangleShape &elem) {
        ::rlPushMatrix();
        ::rlTranslatef(elem.transform.position.x, elem.transform.position.y, 0.0f);
        ::rlRotatef(elem.transform.rotation, 0.0f, 0.0f, 1.0f);
        ::rlScalef(elem.transform.scale.x, elem.transform.scale.y, 1.0f);

        const ::Vector2 v1 = {.x = 0.0f, .y = 0.0f};
        const ::Vector2 v2 = {.x = -elem.size / 2.0f, .y = elem.size};
        const ::Vector2 v3 = {.x = elem.size / 2.0f, .y = elem.size};

        ::DrawTriangle(v1, v2, v3, ToRaylibColor(elem.fillColor));
        ::rlPopMatrix();
    }

    void DeclarativeApp::DrawElement(const VisualElement2D &elem) {
        std::visit([&]<typename T0>(const T0& c) {
            using T = std::decay_t<T0>;

            if (!c.visible) return;

            if constexpr (std::is_same_v<T, Group>) {

                ::rlPushMatrix();
                ::rlTranslatef(c.transform.position.x, c.transform.position.y, 0.0f);
                ::rlRotatef(c.transform.rotation, 0.0f, 0.0f, 1.0f);
                ::rlScalef(c.transform.scale.x, c.transform.scale.y, 1.0f);

                for (const auto& child : c.elements) {
                    DrawElement(child);
                }

                ::rlPopMatrix();

            } else if constexpr (std::is_same_v<T, RectangleShape>) {
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
                    } else if constexpr (std::is_same_v<T, LayerUI>) {
                        for (const auto& elem : layer.elements) {
                            DrawElement(elem);
                        }
                    }
                }, layerVariant);
            }
        }
    }

}