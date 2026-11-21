#pragma once
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "audio.hpp"
#include "font.hpp"
#include "texture.hpp"

namespace hooray {

    struct StringHash {
        using is_transparent = void;
        [[nodiscard]] size_t operator()(std::string_view sv) const noexcept {
            return std::hash<std::string_view>{}(sv);
        }
    };

    class AssetManager {
    public:
        AssetManager() = default;
        explicit AssetManager(const AssetManager* fallback) : parent_(fallback) {}

        ~AssetManager() {
            unload_all();
        }

        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;
        AssetManager(AssetManager&&) noexcept = default;
        AssetManager& operator=(AssetManager&&) noexcept = default;

        void set_parent(const AssetManager* parent) noexcept {
            parent_ = parent;
        }

        void queue_texture(TextureAsset asset) {
            queued_textures_.push_back(std::move(asset));
        }

        void queue_font(FontAsset asset) {
            queued_fonts_.push_back(std::move(asset));
        }

        void queue_sound(SoundAsset asset) {
            queued_sounds_.push_back(std::move(asset));
        }

        void queue_music(MusicAsset asset) {
            queued_musics_.push_back(std::move(asset));
        }

        void queue_spritesheet(SpritesheetAsset asset) {
            queued_spritesheets_.push_back(std::move(asset));
        }

        void queue_atlas(AtlasAsset asset) {
            queued_spritesheets_.push_back(SpritesheetAsset{
                .id = std::move(asset.id),
                .path = std::move(asset.path),
                .frame_width = 0.0f,
                .frame_height = 0.0f,
                .regions = std::move(asset.regions)
            });
        }

        void load_all();

        void unload_all() noexcept {
            queued_textures_.clear();
            queued_fonts_.clear();
            queued_sounds_.clear();
            queued_musics_.clear();
            queued_spritesheets_.clear();

            textures_.clear();
            fonts_.clear();
            sounds_.clear();
            musics_.clear();
            spritesheets_.clear();
        }

        [[nodiscard]] const Texture* get_texture(std::string_view id) const {
            if (auto it = textures_.find(id); it != textures_.end()) {
                return &it->second;
            }
            return parent_ ? parent_->get_texture(id) : nullptr;
        }

        [[nodiscard]] const Music* get_music(std::string_view id) const {
            if (auto it = musics_.find(id); it != musics_.end()) {
                return &it->second;
            }
            return parent_ ? parent_->get_music(id) : nullptr;
        }

        [[nodiscard]] const Font* get_font(std::string_view id) const {
            if (auto it = fonts_.find(id); it != fonts_.end()) {
                return &it->second;
            }
            return parent_ ? parent_->get_font(id) : nullptr;
        }

        [[nodiscard]] const Sound* get_sound(std::string_view id) const {
            if (auto it = sounds_.find(id); it != sounds_.end()) {
                return &it->second;
            }
            return parent_ ? parent_->get_sound(id) : nullptr;
        }

        [[nodiscard]] const Spritesheet* get_spritesheet(std::string_view id) const {
            if (auto it = spritesheets_.find(id); it != spritesheets_.end()) {
                return &it->second;
            }
            return parent_ ? parent_->get_spritesheet(id) : nullptr;
        }

    private:
        template <typename T>
        using AssetMap = std::unordered_map<std::string, T, StringHash, std::equal_to<>>;

        const AssetManager* parent_{nullptr};

        std::vector<TextureAsset> queued_textures_;
        std::vector<FontAsset> queued_fonts_;
        std::vector<SoundAsset> queued_sounds_;
        std::vector<MusicAsset> queued_musics_;
        std::vector<SpritesheetAsset> queued_spritesheets_;

        AssetMap<Texture> textures_;
        AssetMap<Font> fonts_;
        AssetMap<Sound> sounds_;
        AssetMap<Music> musics_;
        AssetMap<Spritesheet> spritesheets_;
    };

}