#include "hooray/assets/audio.hpp"
#include <raylib.h>
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

}