#pragma once
#include <map>

#include <hooray/font.hpp>

namespace Hooray {

    class HoorayApp final {
    public:
        explicit HoorayApp(AppConfig config = {});

        ~HoorayApp();

        HoorayApp(const HoorayApp&) = delete;
        HoorayApp& operator=(const HoorayApp&) = delete;

        int Run();

        void InitMusicStreams();
        void UpdateMusicStreams();

        void ProcessWindowFlags();

        void ProcessMouseEvents();
        void ProcessKeyboardEvents();
        void ProcessGamepadEvents();
        void ProcessTouchEvents();

        void DrawElement(const VisualElement2D &elem);

        template<class T>
        void ProcessInit(T &node);

        void OnDraw();

        void LoadGlobalAssets();
        void UnloadGlobalAssets();

        void Quit();

    private:
        AppConfig m_config;
        bool m_running = false;
        std::unordered_map<std::string, Texture> m_textureMap;
        std::unordered_map<std::string, Font> m_fontMap;
        std::unordered_map<std::string, Music> m_musicMap;
        std::unordered_map<std::string, Sound> m_soundMap;
    };

    inline int RunApp(AppConfig config) {
        HoorayApp app(std::move(config));
        return app.Run();
    }

}
