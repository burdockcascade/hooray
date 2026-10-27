#include <raylib.h>
#include "hooray/font.hpp"
#include "../raylibtools.hpp"

namespace Hooray {

    Texture::Texture(const std::filesystem::path& path) noexcept {
        const ::Texture2D raw = ::LoadTexture(path.string().c_str());
        handle_ = {
            .id = raw.id,
            .width = raw.width,
            .height = raw.height,
            .format = raw.format,
            .mipmaps = raw.mipmaps
        };
    }

    Texture::~Texture() noexcept {
        if (handle_.id > 0) {
            ::UnloadTexture(ToRaylibTexture(handle_));
            handle_ = {};
        }
    }

    auto Texture::operator=(Texture&& other) noexcept -> Texture& {
        if (this != &other) {
            if (handle_.id > 0) {
                ::UnloadTexture(ToRaylibTexture(handle_));
            }
            handle_ = std::exchange(other.handle_, TextureHandle{});
        }
        return *this;
    }

    Font::Font(const std::filesystem::path& path, const int baseSize) noexcept {
        const ::Font raw = ::LoadFontEx(path.string().c_str(), baseSize, nullptr, 0);
        handle_ = {
            .baseSize = raw.baseSize,
            .glyphCount = raw.glyphCount,
            .glyphPadding = raw.glyphPadding,
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
        if (handle_.baseSize > 0) {
            ::UnloadFont(ToRaylibFont(handle_));
            handle_ = {};
        }
    }

    auto Font::operator=(Font&& other) noexcept -> Font& {
        if (this != &other) {
            if (handle_.baseSize > 0) {
                ::UnloadFont(ToRaylibFont(handle_));
            }
            handle_ = std::exchange(other.handle_, FontHandle{});
        }
        return *this;
    }

    Sound::Sound(const std::filesystem::path& path) noexcept {
        const ::Sound raw = ::LoadSound(path.string().c_str());
        handle_ = {
            .stream = {
                .buffer = raw.stream.buffer,
                .processor = raw.stream.processor,
                .sampleRate = raw.stream.sampleRate,
                .sampleSize = raw.stream.sampleSize,
                .channels = raw.stream.channels
            },
            .frameCount = raw.frameCount
        };
    }

    Sound::~Sound() noexcept {
        if (handle_.stream.buffer != nullptr) {
            ::UnloadSound(ToRaylibSound(handle_));
            handle_ = {};
        }
    }

    auto Sound::operator=(Sound&& other) noexcept -> Sound& {
        if (this != &other) {
            if (handle_.stream.buffer != nullptr) {
                ::UnloadSound(ToRaylibSound(handle_));
            }
            handle_ = std::exchange(other.handle_, SoundHandle{});
        }
        return *this;
    }

    Music::Music(const std::filesystem::path& path) noexcept {
        if (!::IsAudioDeviceReady()) InitAudioDevice();
        const ::Music raw = ::LoadMusicStream(path.string().c_str());
        handle_ = {
            .stream = {
                .buffer = raw.stream.buffer,
                .processor = raw.stream.processor,
                .sampleRate = raw.stream.sampleRate,
                .sampleSize = raw.stream.sampleSize,
                .channels = raw.stream.channels
            },
            .frameCount = raw.frameCount,
            .looping = raw.looping,
            .ctxType = raw.ctxType,
            .ctxData = raw.ctxData
        };
    }

    void Music::Play() const noexcept {
        if (!::IsAudioDeviceReady()) InitAudioDevice();
        if (handle_.ctxData != nullptr) {
            ::PlayMusicStream(ToRaylibMusic(handle_));
        }
    }

    void Music::Update() const noexcept {
        if (!::IsAudioDeviceReady()) return;
        if (handle_.ctxData != nullptr) {
            ::UpdateMusicStream(ToRaylibMusic(handle_));
        }
    }

    Music::~Music() noexcept {
        if (handle_.ctxData != nullptr) {
            ::UnloadMusicStream(ToRaylibMusic(handle_));
            handle_ = {};
        }
    }

    auto Music::operator=(Music&& other) noexcept -> Music& {
        if (this != &other) {
            if (handle_.ctxData != nullptr) {
                ::UnloadMusicStream(ToRaylibMusic(handle_));
            }
            handle_ = std::exchange(other.handle_, MusicHandle{});
        }
        return *this;
    }

}