#pragma once
#include <cstdint>

// Undefine common macro offenders if pulled in by platform/third-party headers
#undef BLACK
#undef WHITE
#undef RED
#undef GREEN
#undef BLUE
#undef YELLOW
#undef ORANGE
#undef GRAY
#undef DARKGRAY
#undef LIGHTGRAY
#undef MAROON
#undef PINK
#undef LIME
#undef GOLD
#undef PURPLE
#undef VIOLET
#undef MAGENTA
#undef BROWN
#undef BEIGE

namespace hooray {

    struct Color {
        uint8_t r{255};
        uint8_t g{255};
        uint8_t b{255};
        uint8_t a{255};
    };

    namespace colors {

        // Base / Monochrome & Grayscale Ramp
        inline constexpr Color TRANSPARENT   {.r = 0,   .g = 0,   .b = 0,   .a = 0};
        inline constexpr Color WHITE         {.r = 255, .g = 255, .b = 255, .a = 255};
        inline constexpr Color SNOW          {.r = 250, .g = 250, .b = 250, .a = 255};
        inline constexpr Color OFF_WHITE     {.r = 245, .g = 245, .b = 245, .a = 255};
        inline constexpr Color SILVER        {.r = 218, .g = 224, .b = 233, .a = 255};
        inline constexpr Color LIGHT_GRAY    {.r = 200, .g = 200, .b = 200, .a = 255};
        inline constexpr Color SLATE_GRAY    {.r = 112, .g = 128, .b = 144, .a = 255};
        inline constexpr Color GRAY          {.r = 130, .g = 130, .b = 130, .a = 255};
        inline constexpr Color DARK_GRAY     {.r = 80,  .g = 80,  .b = 80,  .a = 255};
        inline constexpr Color CHARCOAL      {.r = 40,  .g = 40,  .b = 40,  .a = 255};
        inline constexpr Color GUNMETAL      {.r = 30,  .g = 34,  .b = 42,  .a = 255};
        inline constexpr Color NIGHT         {.r = 18,  .g = 18,  .b = 20,  .a = 255};
        inline constexpr Color BLACK         {.r = 0,   .g = 0,   .b = 0,   .a = 255};

        // Reds & Warm Pinks
        inline constexpr Color RED           {.r = 230, .g = 41,  .b = 55,  .a = 255};
        inline constexpr Color CRIMSON       {.r = 153, .g = 0,   .b = 0,   .a = 255};
        inline constexpr Color SCARLET       {.r = 255, .g = 36,  .b = 0,   .a = 255};
        inline constexpr Color RUBY          {.r = 224, .g = 17,  .b = 95,  .a = 255};
        inline constexpr Color MAROON        {.r = 190, .g = 33,  .b = 55,  .a = 255};
        inline constexpr Color BURGUNDY      {.r = 128, .g = 0,   .b = 32,  .a = 255};
        inline constexpr Color WINE          {.r = 90,  .g = 15,  .b = 30,  .a = 255};
        inline constexpr Color RUST          {.r = 183, .g = 65,  .b = 14,  .a = 255};
        inline constexpr Color CORAL         {.r = 255, .g = 127, .b = 80,  .a = 255};
        inline constexpr Color SALMON        {.r = 250, .g = 128, .b = 114, .a = 255};
        inline constexpr Color PINK          {.r = 255, .g = 109, .b = 194, .a = 255};
        inline constexpr Color HOT_PINK      {.r = 255, .g = 105, .b = 180, .a = 255};
        inline constexpr Color ROSE          {.r = 255, .g = 182, .b = 193, .a = 255};

        // Oranges & Yellows
        inline constexpr Color ORANGE        {.r = 255, .g = 161, .b = 0,   .a = 255};
        inline constexpr Color DARK_ORANGE   {.r = 255, .g = 140, .b = 0,   .a = 255};
        inline constexpr Color TANGERINE     {.r = 242, .g = 133, .b = 0,   .a = 255};
        inline constexpr Color AMBER         {.r = 255, .g = 191, .b = 0,   .a = 255};
        inline constexpr Color GOLD          {.r = 255, .g = 203, .b = 0,   .a = 255};
        inline constexpr Color YELLOW        {.r = 253, .g = 249, .b = 0,   .a = 255};
        inline constexpr Color LEMON         {.r = 255, .g = 247, .b = 0,   .a = 255};
        inline constexpr Color MUSTARD       {.r = 227, .g = 178, .b = 60,  .a = 255};
        inline constexpr Color PEACH         {.r = 255, .g = 218, .b = 185, .a = 255};
        inline constexpr Color APRICOT       {.r = 251, .g = 206, .b = 177, .a = 255};

        // Greens & Yellow-Greens
        inline constexpr Color GREEN         {.r = 0,   .g = 228, .b = 48,  .a = 255};
        inline constexpr Color BRIGHT_GREEN  {.r = 50,  .g = 205, .b = 50,  .a = 255};
        inline constexpr Color DARK_GREEN    {.r = 0,   .g = 117, .b = 44,  .a = 255};
        inline constexpr Color FOREST_GREEN  {.r = 34,  .g = 139, .b = 34,  .a = 255};
        inline constexpr Color EMERALD       {.r = 46,  .g = 204, .b = 113, .a = 255};
        inline constexpr Color LIME          {.r = 0,   .g = 158, .b = 47,  .a = 255};
        inline constexpr Color NEON_GREEN    {.r = 57,  .g = 255, .b = 20,  .a = 255};
        inline constexpr Color MINT          {.r = 152, .g = 251, .b = 152, .a = 255};
        inline constexpr Color SEAFOAM       {.r = 147, .g = 223, .b = 184, .a = 255};
        inline constexpr Color OLIVE         {.r = 128, .g = 128, .b = 0,   .a = 255};
        inline constexpr Color SAGE          {.r = 138, .g = 154, .b = 91,  .a = 255};
        inline constexpr Color MOSS          {.r = 74,  .g = 93,  .b = 35,  .a = 255};

        // Cyans, Teals & Blues
        inline constexpr Color CYAN          {.r = 0,   .g = 255, .b = 255, .a = 255};
        inline constexpr Color AQUA          {.r = 64,  .g = 224, .b = 208, .a = 255};
        inline constexpr Color TURQUOISE     {.r = 26,  .g = 188, .b = 156, .a = 255};
        inline constexpr Color TEAL          {.r = 0,   .g = 128, .b = 128, .a = 255};
        inline constexpr Color DARK_TEAL     {.r = 0,   .g = 84,  .b = 84,  .a = 255};
        inline constexpr Color SKY_BLUE      {.r = 102, .g = 191, .b = 255, .a = 255};
        inline constexpr Color LIGHT_BLUE    {.r = 173, .g = 216, .b = 230, .a = 255};
        inline constexpr Color ICE_BLUE      {.r = 208, .g = 232, .b = 242, .a = 255};
        inline constexpr Color BLUE          {.r = 0,   .g = 121, .b = 241, .a = 255};
        inline constexpr Color ROYAL_BLUE    {.r = 65,  .g = 105, .b = 225, .a = 255};
        inline constexpr Color COBALT        {.r = 0,   .g = 71,  .b = 171, .a = 255};
        inline constexpr Color DARK_BLUE     {.r = 0,   .g = 82,  .b = 172, .a = 255};
        inline constexpr Color NAVY          {.r = 0,   .g = 32,  .b = 96,  .a = 255};
        inline constexpr Color MIDNIGHT_BLUE {.r = 25,  .g = 25,  .b = 112, .a = 255};

        // Purples, Violets & Magentas
        inline constexpr Color PURPLE        {.r = 200, .g = 122, .b = 255, .a = 255};
        inline constexpr Color DEEP_PURPLE   {.r = 102, .g = 51,  .b = 153, .a = 255};
        inline constexpr Color LAVENDER      {.r = 230, .g = 190, .b = 255, .a = 255};
        inline constexpr Color LILAC         {.r = 200, .g = 162, .b = 200, .a = 255};
        inline constexpr Color INDIGO        {.r = 75,  .g = 0,   .b = 130, .a = 255};
        inline constexpr Color VIOLET        {.r = 135, .g = 60,  .b = 190, .a = 255};
        inline constexpr Color PLUM          {.r = 142, .g = 68,  .b = 173, .a = 255};
        inline constexpr Color MAGENTA       {.r = 255, .g = 0,   .b = 255, .a = 255};
        inline constexpr Color FUCHSIA       {.r = 255, .g = 0,   .b = 128, .a = 255};

        // Browns, Earth & Skin Tones
        inline constexpr Color BROWN         {.r = 127, .g = 106, .b = 79,  .a = 255};
        inline constexpr Color DARK_BROWN    {.r = 76,  .g = 63,  .b = 47,  .a = 255};
        inline constexpr Color CHOCOLATE     {.r = 60,  .g = 34,  .b = 21,  .a = 255};
        inline constexpr Color COFFEE        {.r = 111, .g = 78,  .b = 55,  .a = 255};
        inline constexpr Color COPPER        {.r = 184, .g = 115, .b = 51,  .a = 255};
        inline constexpr Color BRONZE        {.r = 205, .g = 127, .b = 50,  .a = 255};
        inline constexpr Color TAN           {.r = 210, .g = 180, .b = 140, .a = 255};
        inline constexpr Color KHAKI         {.r = 195, .g = 176, .b = 145, .a = 255};
        inline constexpr Color BEIGE         {.r = 211, .g = 176, .b = 131, .a = 255};
        inline constexpr Color SAND          {.r = 238, .g = 214, .b = 175, .a = 255};

        // UI Semantics & State Tints
        inline constexpr Color SUCCESS       {.r = 46,  .g = 204, .b = 113, .a = 255};
        inline constexpr Color SUCCESS_DARK  {.r = 39,  .g = 174, .b = 96,  .a = 255};
        inline constexpr Color WARNING       {.r = 241, .g = 196, .b = 15,  .a = 255};
        inline constexpr Color WARNING_DARK  {.r = 214, .g = 137, .b = 16,  .a = 255};
        inline constexpr Color DANGER        {.r = 231, .g = 76,  .b = 60,  .a = 255};
        inline constexpr Color DANGER_DARK   {.r = 192, .g = 57,  .b = 43,  .a = 255};
        inline constexpr Color INFO          {.r = 52,  .g = 152, .b = 219, .a = 255};
        inline constexpr Color INFO_DARK     {.r = 41,  .g = 128, .b = 185, .a = 255};

        // Semi-transparent Overlays
        inline constexpr Color SCRIM         {.r = 0,   .g = 0,   .b = 0,   .a = 160};
        inline constexpr Color SHADOW        {.r = 0,   .g = 0,   .b = 0,   .a = 100};
        inline constexpr Color HIGHLIGHT     {.r = 255, .g = 255, .b = 255, .a = 64};
    }

}