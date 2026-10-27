#pragma once
#include <filesystem>
#include <string>
#include <utility>
#include <variant>

namespace Hooray {

#pragma region Texture

    struct TextureHandle {
        uint32_t id{0};
        int width{0};
        int height{0};
        int format{0};
        int mipmaps{0};
    };

    class Texture {
    public:
        explicit Texture(const std::filesystem::path& path) noexcept;
        explicit constexpr Texture(TextureHandle handle = {}) noexcept : handle_{handle} {}

        ~Texture() noexcept;

        Texture(const Texture&) = delete;
        auto operator=(const Texture&) -> Texture& = delete;

        constexpr Texture(Texture&& other) noexcept
            : handle_{std::exchange(other.handle_, TextureHandle{})} {}

        auto operator=(Texture&& other) noexcept -> Texture&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.id > 0;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const TextureHandle& {
            return handle_;
        }

    private:
        TextureHandle handle_{};
    };

    struct TextureAsset {
        std::string id;
        std::filesystem::path path;
    };

#pragma endregion

#pragma region Font

    struct FontHandle {
        int baseSize{0};
        int glyphCount{0};
        int glyphPadding{0};
        TextureHandle texture{};
        void* recs{nullptr};
        void* glyphs{nullptr};
    };

    class Font {
    public:
        explicit Font(const std::filesystem::path& path, int baseSize) noexcept;
        explicit constexpr Font(FontHandle handle = {}) noexcept : handle_{handle} {}

        ~Font() noexcept;

        Font(const Font&) = delete;
        auto operator=(const Font&) -> Font& = delete;

        constexpr Font(Font&& other) noexcept
            : handle_{std::exchange(other.handle_, FontHandle{})} {}

        auto operator=(Font&& other) noexcept -> Font&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.baseSize > 0;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const FontHandle& {
            return handle_;
        }

    private:
        FontHandle handle_{};
    };

    struct FontAsset {
        std::string id;
        std::filesystem::path path;
        int baseSize{32};
    };

#pragma endregion

#pragma region Audio Handles & Common Types

    // Matches raylib's AudioStream layout:
    // rAudioBuffer* buffer, rAudioProcessor* processor, sampleRate, sampleSize, channels
    struct AudioStreamHandle {
        void* buffer{nullptr};
        void* processor{nullptr};
        uint32_t sampleRate{0};
        uint32_t sampleSize{0};
        uint32_t channels{0};
    };

#pragma endregion

#pragma region Sound

    // Matches raylib's Sound: AudioStream stream, unsigned int frameCount
    struct SoundHandle {
        AudioStreamHandle stream{};
        uint32_t frameCount{0};
    };

    class Sound {
    public:
        explicit Sound(const std::filesystem::path& path) noexcept;

        explicit constexpr Sound(SoundHandle handle = {}) noexcept : handle_{handle} {}

        ~Sound() noexcept;

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
        std::filesystem::path path;
    };

#pragma endregion

#pragma region Music

    // Matches raylib's Music: AudioStream stream, frameCount, looping, ctxType, ctxData
    struct MusicHandle {
        AudioStreamHandle stream{};
        uint32_t frameCount{0};
        bool looping{true};
        int ctxType{0};
        void* ctxData{nullptr};
    };

    class Music {
    public:
        explicit Music(const std::filesystem::path& path) noexcept;

        void Play() const noexcept;

        void Update() const noexcept;

        explicit constexpr Music(MusicHandle handle = {}) noexcept : handle_{handle} {}

        ~Music() noexcept;

        Music(const Music&) = delete;
        auto operator=(const Music&) -> Music& = delete;

        constexpr Music(Music&& other) noexcept
            : handle_{std::exchange(other.handle_, MusicHandle{})} {}

        auto operator=(Music&& other) noexcept -> Music&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.ctxData != nullptr;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const MusicHandle& {
            return handle_;
        }

    private:
        MusicHandle handle_{};
    };

    struct MusicAsset {
        std::string id;
        std::filesystem::path path;
    };

#pragma endregion

    using Asset = std::variant<TextureAsset, FontAsset, SoundAsset, MusicAsset>;

}