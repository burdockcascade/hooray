#pragma once
#include <cstdint>
#include <string>
#include <utility>

namespace hooray {

    struct AudioStreamHandle {
        void* buffer{nullptr};
        void* processor{nullptr};
        uint32_t sample_rate{0};
        uint32_t sample_size{0};
        uint32_t channels{0};
    };

    struct SoundHandle {
        AudioStreamHandle stream{};
        uint32_t frame_count{0};
    };

    class Sound {
    public:
        explicit Sound(const std::string& path) noexcept;
        explicit constexpr Sound(SoundHandle handle = {}) noexcept : handle_{handle} {}

        ~Sound() noexcept;

        void play() const noexcept;
        void stop() const noexcept;

        Sound(const Sound&) = delete;
        auto operator=(const Sound&) -> Sound& = delete;

        constexpr Sound(Sound&& other) noexcept
            : handle_{std::exchange(other.handle_, SoundHandle{})} {}

        auto operator=(Sound&& other) noexcept -> Sound&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.stream.buffer != nullptr;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const SoundHandle& {
            return handle_;
        }

    private:
        SoundHandle handle_{};
    };

    struct SoundAsset {
        std::string id;
        std::string path;
    };

    struct MusicHandle {
        AudioStreamHandle stream{};
        uint32_t frame_count{0};
        bool looping{true};
        int ctx_type{0};
        void* ctx_data{nullptr};
    };

    class Music {
    public:
        explicit Music(const std::string& path) noexcept;
        explicit constexpr Music(MusicHandle handle = {}) noexcept : handle_{handle} {}

        ~Music() noexcept;

        void play() const noexcept;
        void stop() const noexcept;
        void pause() const noexcept;
        void resume() const noexcept;
        void update() const noexcept;
        void set_looping(bool loop) noexcept { handle_.looping = loop; }

        Music(const Music&) = delete;
        auto operator=(const Music&) -> Music& = delete;

        constexpr Music(Music&& other) noexcept
            : handle_{std::exchange(other.handle_, MusicHandle{})} {}

        auto operator=(Music&& other) noexcept -> Music&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.ctx_data != nullptr;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const MusicHandle& {
            return handle_;
        }

    private:
        MusicHandle handle_{};
    };

    struct MusicAsset {
        std::string id;
        std::string path;
    };

}