#pragma once
#include <functional>
#include <memory>
#include <string>
#include <variant>

namespace Hooray {

#pragma region NodeController

    template <typename T>
    struct NodeController {
        virtual ~NodeController() = default;

        // Lifecycle
        virtual void OnInit(T& node) {};
        virtual void OnUpdate(float dt, T& node) {};
        virtual void OnDestroy(float dt, T& node) { };

    };

    template <typename T>
    struct NodeCallbacks {
        std::function<void(T& node)> onInit{nullptr};
        std::function<void(float dt, T& node)> onUpdate{nullptr};
        std::function<void(T& node)> onDestroy{nullptr};
    };

    template <typename T>
    using ControllerSlot = std::variant<
        std::monostate,                         // empty / no controller
        NodeCallbacks<T>,                       // lightweight callbacks
        std::shared_ptr<NodeController<T>>      // class-based controller
    >;

#pragma endregion

#pragma region Types

    struct Color {
        uint8_t r{255};
        uint8_t g{255};
        uint8_t b{255};
        uint8_t a{255};
    };

    struct Vector2 {
        float x{0.0f};
        float y{0.0f};
    };

#pragma endregion

#pragma region Color

    namespace Colors {
        // Base / Monochrome & Grayscale Ramp
        inline constexpr Color Transparent  {.r = 0,   .g = 0,   .b = 0,   .a = 0};
        inline constexpr Color White        {.r = 255, .g = 255, .b = 255, .a = 255};
        inline constexpr Color Snow         {.r = 250, .g = 250, .b = 250, .a = 255};
        inline constexpr Color OffWhite     {.r = 245, .g = 245, .b = 245, .a = 255};
        inline constexpr Color Silver       {.r = 218, .g = 224, .b = 233, .a = 255};
        inline constexpr Color LightGray    {.r = 200, .g = 200, .b = 200, .a = 255};
        inline constexpr Color SlateGray    {.r = 112, .g = 128, .b = 144, .a = 255};
        inline constexpr Color Gray         {.r = 130, .g = 130, .b = 130, .a = 255};
        inline constexpr Color DarkGray     {.r = 80,  .g = 80,  .b = 80,  .a = 255};
        inline constexpr Color Charcoal     {.r = 40,  .g = 40,  .b = 40,  .a = 255};
        inline constexpr Color Gunmetal     {.r = 30,  .g = 34,  .b = 42,  .a = 255};
        inline constexpr Color Night        {.r = 18,  .g = 18,  .b = 20,  .a = 255};
        inline constexpr Color Black        {.r = 0,   .g = 0,   .b = 0,   .a = 255};

        // Reds & Warm Pinks
        inline constexpr Color Red          {.r = 230, .g = 41,  .b = 55,  .a = 255};
        inline constexpr Color Crimson      {.r = 153, .g = 0,   .b = 0,   .a = 255};
        inline constexpr Color Scarlet      {.r = 255, .g = 36,  .b = 0,   .a = 255};
        inline constexpr Color Ruby         {.r = 224, .g = 17,  .b = 95,  .a = 255};
        inline constexpr Color Maroon       {.r = 190, .g = 33,  .b = 55,  .a = 255};
        inline constexpr Color Burgundy     {.r = 128, .g = 0,   .b = 32,  .a = 255};
        inline constexpr Color Wine         {.r = 90,  .g = 15,  .b = 30,  .a = 255};
        inline constexpr Color Rust         {.r = 183, .g = 65,  .b = 14,  .a = 255};
        inline constexpr Color Coral        {.r = 255, .g = 127, .b = 80,  .a = 255};
        inline constexpr Color Salmon       {.r = 250, .g = 128, .b = 114, .a = 255};
        inline constexpr Color Pink         {.r = 255, .g = 109, .b = 194, .a = 255};
        inline constexpr Color HotPink      {.r = 255, .g = 105, .b = 180, .a = 255};
        inline constexpr Color Rose         {.r = 255, .g = 182, .b = 193, .a = 255};

        // Oranges & Yellows
        inline constexpr Color Orange       {.r = 255, .g = 161, .b = 0,   .a = 255};
        inline constexpr Color DarkOrange   {.r = 255, .g = 140, .b = 0,   .a = 255};
        inline constexpr Color Tangerine    {.r = 242, .g = 133, .b = 0,   .a = 255};
        inline constexpr Color Amber        {.r = 255, .g = 191, .b = 0,   .a = 255};
        inline constexpr Color Gold         {.r = 255, .g = 203, .b = 0,   .a = 255};
        inline constexpr Color Yellow       {.r = 253, .g = 249, .b = 0,   .a = 255};
        inline constexpr Color Lemon        {.r = 255, .g = 247, .b = 0,   .a = 255};
        inline constexpr Color Mustard      {.r = 227, .g = 178, .b = 60,  .a = 255};
        inline constexpr Color Peach        {.r = 255, .g = 218, .b = 185, .a = 255};
        inline constexpr Color Apricot      {.r = 251, .g = 206, .b = 177, .a = 255};

        // Greens & Yellow-Greens
        inline constexpr Color Green        {.r = 0,   .g = 228, .b = 48,  .a = 255};
        inline constexpr Color BrightGreen  {.r = 50,  .g = 205, .b = 50,  .a = 255};
        inline constexpr Color DarkGreen    {.r = 0,   .g = 117, .b = 44,  .a = 255};
        inline constexpr Color ForestGreen  {.r = 34,  .g = 139, .b = 34,  .a = 255};
        inline constexpr Color Emerald      {.r = 46,  .g = 204, .b = 113, .a = 255};
        inline constexpr Color Lime         {.r = 0,   .g = 158, .b = 47,  .a = 255};
        inline constexpr Color NeonGreen    {.r = 57,  .g = 255, .b = 20,  .a = 255};
        inline constexpr Color Mint         {.r = 152, .g = 251, .b = 152, .a = 255};
        inline constexpr Color Seafoam      {.r = 147, .g = 223, .b = 184, .a = 255};
        inline constexpr Color Olive        {.r = 128, .g = 128, .b = 0,   .a = 255};
        inline constexpr Color Sage         {.r = 138, .g = 154, .b = 91,  .a = 255};
        inline constexpr Color Moss         {.r = 74,  .g = 93,  .b = 35,  .a = 255};

        // Cyans, Teals & Blues
        inline constexpr Color Cyan         {.r = 0,   .g = 255, .b = 255, .a = 255};
        inline constexpr Color Aqua         {.r = 64,  .g = 224, .b = 208, .a = 255};
        inline constexpr Color Turquoise    {.r = 26,  .g = 188, .b = 156, .a = 255};
        inline constexpr Color Teal         {.r = 0,   .g = 128, .b = 128, .a = 255};
        inline constexpr Color DarkTeal     {.r = 0,   .g = 84,  .b = 84,  .a = 255};
        inline constexpr Color SkyBlue      {.r = 102, .g = 191, .b = 255, .a = 255};
        inline constexpr Color LightBlue    {.r = 173, .g = 216, .b = 230, .a = 255};
        inline constexpr Color IceBlue      {.r = 208, .g = 232, .b = 242, .a = 255};
        inline constexpr Color Blue         {.r = 0,   .g = 121, .b = 241, .a = 255};
        inline constexpr Color RoyalBlue    {.r = 65,  .g = 105, .b = 225, .a = 255};
        inline constexpr Color Cobalt       {.r = 0,   .g = 71,  .b = 171, .a = 255};
        inline constexpr Color DarkBlue     {.r = 0,   .g = 82,  .b = 172, .a = 255};
        inline constexpr Color Navy         {.r = 0,   .g = 32,  .b = 96,  .a = 255};
        inline constexpr Color MidnightBlue {.r = 25,  .g = 25,  .b = 112, .a = 255};

        // Purples, Violets & Magentas
        inline constexpr Color Purple       {.r = 200, .g = 122, .b = 255, .a = 255};
        inline constexpr Color DeepPurple   {.r = 102, .g = 51,  .b = 153, .a = 255};
        inline constexpr Color Lavender     {.r = 230, .g = 190, .b = 255, .a = 255};
        inline constexpr Color Lilac        {.r = 200, .g = 162, .b = 200, .a = 255};
        inline constexpr Color Indigo       {.r = 75,  .g = 0,   .b = 130, .a = 255};
        inline constexpr Color Violet       {.r = 135, .g = 60,  .b = 190, .a = 255};
        inline constexpr Color Plum         {.r = 142, .g = 68,  .b = 173, .a = 255};
        inline constexpr Color Magenta      {.r = 255, .g = 0,   .b = 255, .a = 255};
        inline constexpr Color Fuchsia      {.r = 255, .g = 0,   .b = 128, .a = 255};

        // Browns, Earth & Skin Tones
        inline constexpr Color Brown        {.r = 127, .g = 106, .b = 79,  .a = 255};
        inline constexpr Color DarkBrown    {.r = 76,  .g = 63,  .b = 47,  .a = 255};
        inline constexpr Color Chocolate    {.r = 60,  .g = 34,  .b = 21,  .a = 255};
        inline constexpr Color Coffee       {.r = 111, .g = 78,  .b = 55,  .a = 255};
        inline constexpr Color Copper       {.r = 184, .g = 115, .b = 51,  .a = 255};
        inline constexpr Color Bronze       {.r = 205, .g = 127, .b = 50,  .a = 255};
        inline constexpr Color Tan          {.r = 210, .g = 180, .b = 140, .a = 255};
        inline constexpr Color Khaki        {.r = 195, .g = 176, .b = 145, .a = 255};
        inline constexpr Color Beige        {.r = 211, .g = 176, .b = 131, .a = 255};
        inline constexpr Color Sand         {.r = 238, .g = 214, .b = 175, .a = 255};

        // UI Semantics & State Tints
        inline constexpr Color Success      {.r = 46,  .g = 204, .b = 113, .a = 255};
        inline constexpr Color SuccessDark  {.r = 39,  .g = 174, .b = 96,  .a = 255};
        inline constexpr Color Warning      {.r = 241, .g = 196, .b = 15,  .a = 255};
        inline constexpr Color WarningDark  {.r = 214, .g = 137, .b = 16,  .a = 255};
        inline constexpr Color Danger       {.r = 231, .g = 76,  .b = 60,  .a = 255};
        inline constexpr Color DangerDark   {.r = 192, .g = 57,  .b = 43,  .a = 255};
        inline constexpr Color Info         {.r = 52,  .g = 152, .b = 219, .a = 255};
        inline constexpr Color InfoDark     {.r = 41,  .g = 128, .b = 185, .a = 255};

        // Semi-transparent Overlays
        inline constexpr Color Scrim        {.r = 0,   .g = 0,   .b = 0,   .a = 160};
        inline constexpr Color Shadow       {.r = 0,   .g = 0,   .b = 0,   .a = 100};
        inline constexpr Color Highlight    {.r = 255, .g = 255, .b = 255, .a = 64};
    }

#pragma endregion

#pragma region Node2D

    struct RectangleShape {
        bool active{true};
        bool visible{true};
        Vector2 position{.x = 0.0f, .y = 0.0f};
        Vector2 size{.x = 100.0f, .y = 100.0f};
        Color fillColor{Colors::White};
        ControllerSlot<RectangleShape> controller{};
    };

    struct CircleShape {
        bool active{true};
        bool visible{true};
        Vector2 position{.x = 0.0f, .y = 0.0f};
        float radius{50.0f};
        Color fillColor{Colors::White};
        ControllerSlot<CircleShape> controller{};
    };

    struct TriangleShape {
        bool active{true};
        bool visible{true};
        Vector2 position{.x = 0.0f, .y = 0.0f};
        float size{50.0f};
        Color fillColor{Colors::White};
    };

    using VisualElement2D = std::variant<RectangleShape, CircleShape, TriangleShape>;

#pragma endregion

#pragma region Scene

    struct Camera2D {
        bool active{true};
        bool visible{true};
        Vector2 target{.x = 0.0f, .y = 0.0f};
        Vector2 offset{.x = 0.0f, .y = 0.0f};
        float rotation{0.0f};
        float zoom{1.0f};
    };

    struct LayerUI {
        bool active{true};
        bool visible{true};
        std::vector<VisualElement2D> elements{};
    };

    struct Layer2D {
        bool active{true};
        bool visible{true};
        Camera2D camera{};
        std::vector<VisualElement2D> elements{};
    };

    struct Layer3D {
        // Placeholder for future 3D layer implementation
        bool active{true};
        bool visible{true};
    };

    using Layer = std::variant<LayerUI, Layer2D, Layer3D>;

    struct Scene {
        bool active{true};
        bool visible{true};
        std::vector<Layer> layers{};
    };

#pragma endregion

#pragma region Window

    struct WindowConfig {
        std::string title = "Hooray App";
        int width = 1280;
        int height = 720;
        Color bgColor{Colors::White};
        int targetFps = 60;
        bool resizable = false;
        bool showFPS = false;
    };

    struct AppConfig {
        WindowConfig window{};
        std::vector<Scene> scenes{};
    };

#pragma endregion

}
