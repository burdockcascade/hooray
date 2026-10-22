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
        void quit();

    private:
        AppConfig m_config;
        bool m_running = false;
    };

    inline int RunApp(AppConfig config) {
        DeclarativeApp app(std::move(config));
        return app.run();
    }

}
