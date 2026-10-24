#pragma once
#include <map>

#include <hooray/scenegraph.hpp>

namespace Hooray {

    class DeclarativeApp final {
    public:
        explicit DeclarativeApp(AppConfig config = {});

        ~DeclarativeApp();

        DeclarativeApp(const DeclarativeApp&) = delete;
        DeclarativeApp& operator=(const DeclarativeApp&) = delete;

        int run();

        void DrawElement(const VisualElement2D &elem);

        template<class T>
        void ProcessInit(T &node);

        void OnDraw();

        void quit();

    private:
        AppConfig m_config;
        bool m_running = false;
        std::unordered_map<std::string, Texture> m_textureMap;
        std::unordered_map<std::string, Font> m_fontMap;
    };

    inline int RunApp(AppConfig config) {
        DeclarativeApp app(std::move(config));
        return app.run();
    }

}
