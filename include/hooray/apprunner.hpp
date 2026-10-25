#pragma once
#include <map>

#include <hooray/scenegraph.hpp>

namespace Hooray {

    class HoorayApp final {
    public:
        explicit HoorayApp(AppConfig config = {});

        ~HoorayApp();

        HoorayApp(const HoorayApp&) = delete;
        HoorayApp& operator=(const HoorayApp&) = delete;

        int run();

        void ProcessMouseEvents();
        void ProcessKeyboardEvents();

        void DrawElement(const VisualElement2D &elem);

        template<class T>
        void ProcessInit(T &node);

        void OnDraw();

        void LoadGlobalAssets();
        void UnloadGlobalAssets();

        void quit();

    private:
        AppConfig m_config;
        bool m_running = false;
        std::unordered_map<std::string, Texture> m_textureMap;
        std::unordered_map<std::string, Font> m_fontMap;
    };

    inline int RunApp(AppConfig config) {
        HoorayApp app(std::move(config));
        return app.run();
    }

}
