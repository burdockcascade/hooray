#include "hooray/assets/assetmanager.hpp"
#include <raylib.h>

namespace hooray {

    static Spritesheet load_spritesheet_asset(SpritesheetAsset item) {
        Texture tex(item.path);
        const auto& handle = tex.handle();

        std::vector<TextureRegion> regions = std::move(item.regions);

        // Guard against division by zero when frame dimensions are < 1.0f
        if (regions.empty() && item.frame_width >= 1.0f && item.frame_height >= 1.0f && tex.is_valid()) {
            const int cols = static_cast<int>(static_cast<float>(handle.width) / item.frame_width);
            const int rows = static_cast<int>(static_cast<float>(handle.height) / item.frame_height);

            if (cols > 0 && rows > 0) {
                regions.reserve(static_cast<size_t>(cols) * static_cast<size_t>(rows));
                for (int y = 0; y < rows; ++y) {
                    for (int x = 0; x < cols; ++x) {
                        regions.push_back({
                            .x = static_cast<float>(x) * item.frame_width,
                            .y = static_cast<float>(y) * item.frame_height,
                            .width = item.frame_width,
                            .height = item.frame_height
                        });
                    }
                }
            }
        }

        return Spritesheet{
            .texture = std::move(tex),
            .frame_width = item.frame_width,
            .frame_height = item.frame_height,
            .regions = std::move(regions)
        };
    }

    void AssetManager::load_all() {
        for (auto& item : queued_textures_) {
            textures_.insert_or_assign(std::move(item.id), Texture(item.path));
        }
        queued_textures_.clear();

        for (auto& item : queued_fonts_) {
            fonts_.insert_or_assign(std::move(item.id), Font(item.path, item.base_size));
        }
        queued_fonts_.clear();

        for (auto& item : queued_sounds_) {
            sounds_.insert_or_assign(std::move(item.id), Sound(item.path));
        }
        queued_sounds_.clear();

        for (auto& item : queued_musics_) {
            musics_.insert_or_assign(std::move(item.id), Music(item.path));
        }
        queued_musics_.clear();

        for (auto& item : queued_spritesheets_) {
            std::string id = std::move(item.id);
            spritesheets_.insert_or_assign(std::move(id), load_spritesheet_asset(std::move(item)));
        }
        queued_spritesheets_.clear();
    }

}