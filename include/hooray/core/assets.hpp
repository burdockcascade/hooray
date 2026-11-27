#pragma once
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace hooray {

    struct TextureHandle {
        uint32_t id{0};
        int width{0};
        int height{0};
        int format{0};
        int mipmaps{0};
    };

    class Texture {
    public:
        explicit Texture(const std::string& path) noexcept;
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
        std::string path;
    };

    struct TextureRegion {
        float x{0.0f};
        float y{0.0f};
        float width{0.0f};
        float height{0.0f};
    };

    struct Spritesheet {
        Texture texture{};
        float frame_width{0.0f};
        float frame_height{0.0f};
        std::vector<TextureRegion> regions;
    };

    struct AtlasAsset {
        std::string id;
        std::string path;
        std::vector<TextureRegion> regions{};
    };

    struct SpritesheetAsset {
        std::string id;
        std::string path;
        float frame_width{0.0f};
        float frame_height{0.0f};
        std::vector<TextureRegion> regions{};
    };

    struct FontHandle {
        int base_size{0};
        int glyph_count{0};
        int glyph_padding{0};
        TextureHandle texture{};
        void* recs{nullptr};
        void* glyphs{nullptr};
    };

    class Font {
    public:
        explicit Font(const std::string& path, int base_size) noexcept;
        explicit constexpr Font(FontHandle handle = {}) noexcept : handle_{handle} {}

        ~Font() noexcept;

        Font(const Font&) = delete;
        auto operator=(const Font&) -> Font& = delete;

        constexpr Font(Font&& other) noexcept
            : handle_{std::exchange(other.handle_, FontHandle{})} {}

        auto operator=(Font&& other) noexcept -> Font&;

        [[nodiscard]] constexpr auto is_valid() const noexcept -> bool {
            return handle_.texture.id > 0 && handle_. base_size > 0;
        }

        [[nodiscard]] constexpr auto handle() const noexcept -> const FontHandle& {
            return handle_;
        }

    private:
        FontHandle handle_{};
    };

    struct FontAsset {
        std::string id;
        std::string path;
        int base_size{32};
    };

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