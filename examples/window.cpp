#include <hooray.hpp>

int main() {
    return Hooray::RunApp({
        .window = {
            .title = "Hooray Demo",
            .width = 800,
            .height = 600,
            .bgColor = Hooray::Colors::SkyBlue,
            .targetFps = 60
        },
    });
}
