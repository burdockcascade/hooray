#include <array>
#include <hooray/apprunner.hpp>
#include <iostream>
#include <ranges>
#include "raylibtools.hpp"
#include "raylib.h"
#include "rlgl.h"

namespace Hooray {

    namespace {

#pragma region Mouse

        struct MouseBinding {
            MouseButton hoorayButton;
            int raylibButton;
        };

        inline constexpr MouseBinding TrackedMouseBindings[] = {
            { MouseButton::Left,    ::MOUSE_BUTTON_LEFT },
            { MouseButton::Right,   ::MOUSE_BUTTON_RIGHT },
            { MouseButton::Middle,  ::MOUSE_BUTTON_MIDDLE },
            { MouseButton::Side,    ::MOUSE_BUTTON_SIDE },
            { MouseButton::Extra,   ::MOUSE_BUTTON_EXTRA },
            { MouseButton::Forward, ::MOUSE_BUTTON_FORWARD },
            { MouseButton::Back,    ::MOUSE_BUTTON_BACK }
        };

#pragma endregion

#pragma region Keyboard

        struct KeyBinding {
            Key hoorayKey;
            int raylibKey;
        };

        // Pre-paired key mappings: evaluated at compile-time, zero switch overhead
        inline constexpr KeyBinding TrackedKeyBindings[] = {
            { Key::Space, ::KEY_SPACE },
            { Key::Escape, ::KEY_ESCAPE },
            { Key::Enter, ::KEY_ENTER },
            { Key::Tab, ::KEY_TAB },
            { Key::Backspace, ::KEY_BACKSPACE },
            { Key::Insert, ::KEY_INSERT },
            { Key::Delete, ::KEY_DELETE },

            { Key::Right, ::KEY_RIGHT },
            { Key::Left, ::KEY_LEFT },
            { Key::Down, ::KEY_DOWN },
            { Key::Up, ::KEY_UP },
            { Key::PageUp, ::KEY_PAGE_UP },
            { Key::PageDown, ::KEY_PAGE_DOWN },
            { Key::Home, ::KEY_HOME },
            { Key::End, ::KEY_END },

            { Key::CapsLock, ::KEY_CAPS_LOCK },
            { Key::ScrollLock, ::KEY_SCROLL_LOCK },
            { Key::NumLock, ::KEY_NUM_LOCK },
            { Key::PrintScreen, ::KEY_PRINT_SCREEN },
            { Key::Pause, ::KEY_PAUSE },

            { Key::Zero, ::KEY_ZERO },
            { Key::One, ::KEY_ONE },
            { Key::Two, ::KEY_TWO },
            { Key::Three, ::KEY_THREE },
            { Key::Four, ::KEY_FOUR },
            { Key::Five, ::KEY_FIVE },
            { Key::Six, ::KEY_SIX },
            { Key::Seven, ::KEY_SEVEN },
            { Key::Eight, ::KEY_EIGHT },
            { Key::Nine, ::KEY_NINE },

            { Key::A, ::KEY_A },
            { Key::B, ::KEY_B },
            { Key::C, ::KEY_C },
            { Key::D, ::KEY_D },
            { Key::E, ::KEY_E },
            { Key::F, ::KEY_F },
            { Key::G, ::KEY_G },
            { Key::H, ::KEY_H },
            { Key::I, ::KEY_I },
            { Key::J, ::KEY_J },
            { Key::K, ::KEY_K },
            { Key::L, ::KEY_L },
            { Key::M, ::KEY_M },
            { Key::N, ::KEY_N },
            { Key::O, ::KEY_O },
            { Key::P, ::KEY_P },
            { Key::Q, ::KEY_Q },
            { Key::R, ::KEY_R },
            { Key::S, ::KEY_S },
            { Key::T, ::KEY_T },
            { Key::U, ::KEY_U },
            { Key::V, ::KEY_V },
            { Key::W, ::KEY_W },
            { Key::X, ::KEY_X },
            { Key::Y, ::KEY_Y },
            { Key::Z, ::KEY_Z },

            { Key::F1, ::KEY_F1 },
            { Key::F2, ::KEY_F2 },
            { Key::F3, ::KEY_F3 },
            { Key::F4, ::KEY_F4 },
            { Key::F5, ::KEY_F5 },
            { Key::F6, ::KEY_F6 },
            { Key::F7, ::KEY_F7 },
            { Key::F8, ::KEY_F8 },
            { Key::F9, ::KEY_F9 },
            { Key::F10, ::KEY_F10 },
            { Key::F11, ::KEY_F11 },
            { Key::F12, ::KEY_F12 },

            { Key::LeftShift, ::KEY_LEFT_SHIFT },
            { Key::LeftControl, ::KEY_LEFT_CONTROL },
            { Key::LeftAlt, ::KEY_LEFT_ALT },
            { Key::LeftSuper, ::KEY_LEFT_SUPER },
            { Key::RightShift, ::KEY_RIGHT_SHIFT },
            { Key::RightControl, ::KEY_RIGHT_CONTROL },
            { Key::RightAlt, ::KEY_RIGHT_ALT },
            { Key::RightSuper, ::KEY_RIGHT_SUPER },
            { Key::Menu, ::KEY_KB_MENU },

            { Key::Apostrophe, ::KEY_APOSTROPHE },
            { Key::Comma, ::KEY_COMMA },
            { Key::Minus, ::KEY_MINUS },
            { Key::Period, ::KEY_PERIOD },
            { Key::Slash, ::KEY_SLASH },
            { Key::Semicolon, ::KEY_SEMICOLON },
            { Key::Equal, ::KEY_EQUAL },
            { Key::LeftBracket, ::KEY_LEFT_BRACKET },
            { Key::Backslash, ::KEY_BACKSLASH },
            { Key::RightBracket, ::KEY_RIGHT_BRACKET },
            { Key::Grave, ::KEY_GRAVE },

            { Key::Kp0, ::KEY_KP_0 },
            { Key::Kp1, ::KEY_KP_1 },
            { Key::Kp2, ::KEY_KP_2 },
            { Key::Kp3, ::KEY_KP_3 },
            { Key::Kp4, ::KEY_KP_4 },
            { Key::Kp5, ::KEY_KP_5 },
            { Key::Kp6, ::KEY_KP_6 },
            { Key::Kp7, ::KEY_KP_7 },
            { Key::Kp8, ::KEY_KP_8 },
            { Key::Kp9, ::KEY_KP_9 },
            { Key::KpDecimal, ::KEY_KP_DECIMAL },
            { Key::KpDivide, ::KEY_KP_DIVIDE },
            { Key::KpMultiply, ::KEY_KP_MULTIPLY },
            { Key::KpSubtract, ::KEY_KP_SUBTRACT },
            { Key::KpAdd, ::KEY_KP_ADD },
            { Key::KpEnter, ::KEY_KP_ENTER },
            { Key::KpEqual, ::KEY_KP_EQUAL }
        };

        // Small stack-allocated buffer to store events generated this frame
        constexpr size_t MaxEventsPerFrame = 64;

#pragma endregion

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

        template <typename T>
        void ProcessMouseEvent(const MouseEvent& event, T& node) {
            if constexpr (requires { node.controller; }) {
                std::visit([&](auto& ctrl) {
                    using SlotType = std::decay_t<decltype(ctrl)>;
                    if constexpr (std::is_same_v<SlotType, NodeCallbacks<T>>) {
                        if (ctrl.onMouseEvent) ctrl.onMouseEvent(event, node);
                    } else if constexpr (std::is_same_v<SlotType, std::shared_ptr<NodeController<T>>>) {
                        if (ctrl) ctrl->OnMouseEvent(event, node);
                    }
                }, node.controller);
            }
        }

    }

    HoorayApp::HoorayApp(AppConfig config) : m_config(std::move(config)) {}

    int HoorayApp::run() {

        if (m_config.window.flags.resizable) {
            ::SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        }

        ::InitWindow(m_config.window.width, m_config.window.height, m_config.window.title.c_str());
        ::SetTargetFPS(m_config.window.targetFps);

        LoadGlobalAssets();

        m_running = true;

        // Initialize all controllers
        ForEachActiveElement(m_config.scenes, [this](auto& elem) {
            ProcessInit(elem);
        });

        // Main Game Loop
        while (m_running && !::WindowShouldClose()) {
            const float dt = ::GetFrameTime();

            ProcessMouseEvents();
            ProcessKeyboardEvents();
            ProcessGamepadEvents();
            ProcessTouchEvents();

            // Update controllers
            ForEachActiveElement(m_config.scenes, [dt](auto& elem) {
                ProcessUpdate(dt, elem);
            });

            ::BeginDrawing();
            ::ClearBackground(ToRaylibColor(m_config.window.bgColor));

            OnDraw();
            ::EndDrawing();
        }

        // Cleanup controllers
        const float lastDt = ::GetFrameTime();
        ForEachActiveElement(m_config.scenes, [lastDt](auto& elem) {
            ProcessDestroy(lastDt, elem);
        });

        return 0;
    }

    void HoorayApp::ProcessMouseEvents() {

        std::array<MouseEvent, MaxEventsPerFrame> mouseEvents;
        size_t eventCount = 0;

        const ::Vector2 rayMousePos = ::GetMousePosition();
        const ::Vector2 rayMouseDelta = ::GetMouseDelta();
        const ::Vector2 rayMouseWheel = ::GetMouseWheelMoveV();

        const Vector2 mousePos{.x = rayMousePos.x, .y = rayMousePos.y};
        const Vector2 mouseDelta{.x = rayMouseDelta.x, .y = rayMouseDelta.y};
        const Vector2 mouseWheel{.x = rayMouseWheel.x, .y = rayMouseWheel.y};

        // Mouse button states
        for (const auto& binding : TrackedMouseBindings) {
            if (::IsMouseButtonPressed(binding.raylibButton) && eventCount < MaxEventsPerFrame) {
                mouseEvents[eventCount++] = {
                    .action = MouseAction::Pressed,
                    .button = binding.hoorayButton,
                    .position = mousePos,
                    .delta = mouseDelta
                };
            }
            if (::IsMouseButtonDown(binding.raylibButton) && eventCount < MaxEventsPerFrame) {
                mouseEvents[eventCount++] = {
                    .action = MouseAction::Down,
                    .button = binding.hoorayButton,
                    .position = mousePos,
                    .delta = mouseDelta
                };
            }
            if (::IsMouseButtonReleased(binding.raylibButton) && eventCount < MaxEventsPerFrame) {
                mouseEvents[eventCount++] = {
                    .action = MouseAction::Released,
                    .button = binding.hoorayButton,
                    .position = mousePos,
                    .delta = mouseDelta
                };
            }
        }

        // Cursor movement
        if ((mouseDelta.x != 0.0f || mouseDelta.y != 0.0f) && eventCount < MaxEventsPerFrame) {
            mouseEvents[eventCount++] = {
                .action = MouseAction::Moved,
                .button = MouseButton::None,
                .position = mousePos,
                .delta = mouseDelta
            };
        }

        // Wheel scroll
        if ((mouseWheel.x != 0.0f || mouseWheel.y != 0.0f) && eventCount < MaxEventsPerFrame) {
            mouseEvents[eventCount++] = {
                .action = MouseAction::Scrolled,
                .button = MouseButton::None,
                .position = mousePos,
                .delta = mouseDelta,
                .scroll = mouseWheel
            };
        }

        // 4. Dispatch Mouse Events
        if (eventCount > 0) {
            const std::span<const MouseEvent> activeMouseEvents(mouseEvents.data(), eventCount);
            ForEachActiveElement(m_config.scenes, [activeMouseEvents](auto& elem) {
                for (const auto& ev : activeMouseEvents) {
                    ProcessMouseEvent(ev, elem);
                }
            });
        }

    }

    void HoorayApp::ProcessKeyboardEvents() {

        // Gather all key events that actually occurred this frame (Zero allocations)
        std::array<KeyEvent, MaxEventsPerFrame> frameEvents;
        size_t eventCount = 0;

        for (const auto& binding : TrackedKeyBindings) {
            if (::IsKeyPressed(binding.raylibKey)) {
                if (eventCount < MaxEventsPerFrame) {
                    frameEvents[eventCount++] = { .key = binding.hoorayKey, .action = KeyAction::Pressed };
                }
            }
            if (::IsKeyDown(binding.raylibKey)) {
                if (eventCount < MaxEventsPerFrame) {
                    frameEvents[eventCount++] = { .key = binding.hoorayKey, .action = KeyAction::Down };
                }
            }
            if (::IsKeyReleased(binding.raylibKey)) {
                if (eventCount < MaxEventsPerFrame) {
                    frameEvents[eventCount++] = { .key = binding.hoorayKey, .action = KeyAction::Released };
                }
            }
        }

        if (eventCount > 0) {
            const std::span<const KeyEvent> activeEvents(frameEvents.data(), eventCount);
            ForEachActiveElement(m_config.scenes, [activeEvents](auto& elem) {
                for (const auto& ev : activeEvents) {
                    ProcessKeyEvent(ev, elem);
                }
            });
        }

    }

    void HoorayApp::ProcessGamepadEvents() {
        // Placeholder for future gamepad event processing
    }

    void HoorayApp::ProcessTouchEvents() {
        // Placeholder for future touch event processing
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

    static void DrawSpriteElement(const Sprite &elem, const std::unordered_map<std::string, Texture>& textureMap) {
        const auto it = textureMap.find(elem.texture_id);
        if (it == textureMap.end()) {
            std::cerr << "Texture ID not found: " << elem.texture_id << std::endl;
            return;
        }

        const Texture& texture = it->second;

        const auto texW = static_cast<float>(texture.handle().width);
        const auto texH = static_cast<float>(texture.handle().height);

        Vector2 destSize = elem.size;
        if (destSize.x <= 0.0f && destSize.y <= 0.0f) {
            destSize = { .x = texW, .y = texH };
        }

        ::rlPushMatrix();
        ::rlTranslatef(elem.transform.position.x, elem.transform.position.y, 0.0f);
        ::rlRotatef(elem.transform.rotation, 0.0f, 0.0f, 1.0f);
        ::rlScalef(elem.transform.scale.x, elem.transform.scale.y, 1.0f);

        const ::Rectangle srcRect = { 0.0f, 0.0f, texW, texH };
        const ::Rectangle destRect = {
            -destSize.x * elem.transform.origin.x,
            -destSize.y * elem.transform.origin.y,
            destSize.x,
            destSize.y
        };

        ::DrawTexturePro(ToRaylibTexture(texture.handle()), srcRect, destRect, {0.0f, 0.0f}, 0.0f, ToRaylibColor(elem.tint));
        ::rlPopMatrix();
    }

    static void DrawTextElement(const Text& elem, const std::unordered_map<std::string, Font>& fontMap) {
        if (elem.text.empty()) return;

        ::Font raylibFont = ::GetFontDefault();
        if (!elem.font_id.empty()) {
            if (const auto it = fontMap.find(elem.font_id); it != fontMap.end()) {
                raylibFont = ToRaylibFont(it->second.handle());
                elem.fontSize = (elem.fontSize <= 0.0f) ? static_cast<float>(raylibFont.baseSize) : elem.fontSize;
            } else {
                std::cerr << "Font ID not found: " << elem.font_id << ", using default.\n";
            }
        }

        // Measure text dimensions to position according to transform.origin
        const ::Vector2 textSize = ::MeasureTextEx(raylibFont, elem.text.c_str(), elem.fontSize, elem.spacing);

        ::rlPushMatrix();
        ::rlTranslatef(elem.transform.position.x, elem.transform.position.y, 0.0f);
        ::rlRotatef(elem.transform.rotation, 0.0f, 0.0f, 1.0f);
        ::rlScalef(elem.transform.scale.x, elem.transform.scale.y, 1.0f);

        const ::Vector2 localPos = {
            -textSize.x * elem.transform.origin.x,
            -textSize.y * elem.transform.origin.y
        };

        ::DrawTextEx(raylibFont, elem.text.c_str(), localPos, elem.fontSize, elem.spacing, ToRaylibColor(elem.color));
        ::rlPopMatrix();
    }

    void HoorayApp::DrawElement(const VisualElement2D &elem) {
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
            } else if constexpr (std::is_same_v<T, Sprite>) {
                DrawSpriteElement(c, m_textureMap);
            } else if constexpr (std::is_same_v<T, Text>) {
                DrawTextElement(c, m_fontMap);
            }
        }, elem);
    }

    template <typename T>
    void HoorayApp::ProcessInit(T& node) {
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

    void HoorayApp::OnDraw() {
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

        if (m_config.window.flags.showFPS) {
            ::DrawFPS(10, 10);
        }
    }

    void HoorayApp::LoadGlobalAssets() {
        for (auto asset : m_config.assets) {
            std::visit([&]<typename T0>(T0& item) {
                using Tx = std::decay_t<T0>;

                if constexpr (std::is_same_v<Tx, TextureAsset>) {
                    Texture texture(item.path);
                    m_textureMap.insert_or_assign(item.id, std::move(texture));
                } else if constexpr (std::is_same_v<Tx, FontAsset>) {
                    Font font(item.path, item.baseSize);
                    m_fontMap.insert_or_assign(item.id, std::move(font));
                }
            }, asset);
        }
    }

    void HoorayApp::UnloadGlobalAssets() {
        m_textureMap.clear();
        m_fontMap.clear();
    }

    void HoorayApp::quit() {
        m_running = false;
    }

    HoorayApp::~HoorayApp() {
        if (::IsWindowReady()) {
            UnloadGlobalAssets();
            ::CloseWindow();
        } else {
            for (auto &tex: m_textureMap | std::views::values) {
                tex = Texture{};
            }
            for (auto &font: m_fontMap | std::views::values) {
                font = Font{};
            }
        }
    }

}