#include "hooray.hpp"

int main() {

    Hooray::Window window{800, 600, "Basic Window Example"};

    while (!window.ShouldClose()) {
        window.BeginDrawing();
        window.ClearBackground(255, 255, 255);
        window.EndDrawing();
    }
    
    return 0;
}