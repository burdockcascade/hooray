#include <raylib.h>
#include "hooray/core/assets.hpp"
#include "../raylibtools.hpp"

namespace hooray {

    Sound::Sound(const std::string& path) noexcept {
        if (!::IsAudioDeviceReady()) return;
        const ::Sound raw = ::LoadSound(path.c_str());
        handle_ = {
            .stream = {
                .buffer = raw.stream.buffer,
                .processor = raw.stream.processor,
                .sample_rate = raw.stream.sampleRate,
                .sample_size = raw.stream.sampleSize,
                .channels = raw.stream.channels
            },
            .frame_count = raw.frameCount
        };
    }

    void Sound::play() const noexcept {
        if (::IsAudioDeviceReady() && is_valid()) {
            ::PlaySound(to_raylib_sound(handle_));
        }
    }

    void Sound::stop() const noexcept {
        if (::IsAudioDeviceReady() && is_valid()) {
            ::StopSound(to_raylib_sound(handle_));
        }
    }

    Sound::~Sound() noexcept {
        if (is_valid()) {
            ::UnloadSound(to_raylib_sound(handle_));
            handle_ = {};
        }
    }

    auto Sound::operator=(Sound&& other) noexcept -> Sound& {
        if (this != &other) {
            if (is_valid()) {
                ::UnloadSound(to_raylib_sound(handle_));
            }
            handle_ = std::exchange(other.handle_, SoundHandle{});
        }
        return *this;
    }

    Music::Music(const std::string& path) noexcept {
        if (!::IsAudioDeviceReady()) return;
        const ::Music raw = ::LoadMusicStream(path.c_str());
        handle_ = {
            .stream = {
                .buffer = raw.stream.buffer,
                .processor = raw.stream.processor,
                .sample_rate = raw.stream.sampleRate,
                .sample_size = raw.stream.sampleSize,
                .channels = raw.stream.channels
            },
            .frame_count = raw.frameCount,
            .looping = raw.looping,
            .ctx_type = raw.ctxType,
            .ctx_data = raw.ctxData
        };
    }

    void Music::play() const noexcept {
        if (::IsAudioDeviceReady() && is_valid()) {
            ::PlayMusicStream(to_raylib_music(handle_));
        }
    }

    void Music::update() const noexcept {
        if (::IsAudioDeviceReady() && is_valid()) {
            ::UpdateMusicStream(to_raylib_music(handle_));
        }
    }

    void Music::stop() const noexcept {
        if (::IsAudioDeviceReady() && is_valid()) {
            ::StopMusicStream(to_raylib_music(handle_));
        }
    }

    void Music::pause() const noexcept {
        if (::IsAudioDeviceReady() && is_valid()) {
            ::PauseMusicStream(to_raylib_music(handle_));
        }
    }

    void Music::resume() const noexcept {
        if (::IsAudioDeviceReady() && is_valid()) {
            ::ResumeMusicStream(to_raylib_music(handle_));
        }
    }

    Music::~Music() noexcept {
        if (is_valid()) {
            ::UnloadMusicStream(to_raylib_music(handle_));
            handle_ = {};
        }
    }

    auto Music::operator=(Music&& other) noexcept -> Music& {
        if (this != &other) {
            if (is_valid()) {
                ::UnloadMusicStream(to_raylib_music(handle_));
            }
            handle_ = std::exchange(other.handle_, MusicHandle{});
        }
        return *this;
    }

    Font::Font(const std::string& path, const int base_size) noexcept {
        if (!::IsWindowReady()) return;
        const ::Font raw = ::LoadFontEx(path.c_str(), base_size, nullptr, 0);
        handle_ = {
            .base_size = raw.baseSize,
            .glyph_count = raw.glyphCount,
            .glyph_padding = raw.glyphPadding,
            .texture = {
                .id = raw.texture.id,
                .width = raw.texture.width,
                .height = raw.texture.height,
                .format = raw.texture.format,
                .mipmaps = raw.texture.mipmaps
            },
            .recs = raw.recs,
            .glyphs = raw.glyphs
        };
    }

    Font::~Font() noexcept {
        if (is_valid()) {
            ::UnloadFont(to_raylib_font(handle_));
            handle_ = {};
        }
    }

    auto Font::operator=(Font&& other) noexcept -> Font& {
        if (this != &other) {
            if (is_valid()) {
                ::UnloadFont(to_raylib_font(handle_));
            }
            handle_ = std::exchange(other.handle_, FontHandle{});
        }
        return *this;
    }

    Texture::Texture(const std::string& path) noexcept {
        if (!::IsWindowReady()) return;
        const ::Texture2D raw = ::LoadTexture(path.c_str());
        handle_ = {
            .id = raw.id,
            .width = raw.width,
            .height = raw.height,
            .format = raw.format,
            .mipmaps = raw.mipmaps
        };
    }

    Texture::~Texture() noexcept {
        if (is_valid()) {
            ::UnloadTexture(to_raylib_texture(handle_));
            handle_ = {};
        }
    }

    auto Texture::operator=(Texture&& other) noexcept -> Texture& {
        if (this != &other) {
            if (is_valid()) {
                ::UnloadTexture(to_raylib_texture(handle_));
            }
            handle_ = std::exchange(other.handle_, TextureHandle{});
        }
        return *this;
    }

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