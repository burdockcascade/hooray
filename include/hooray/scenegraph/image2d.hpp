#pragma once

#include "node.hpp"
#include "../core/assets.hpp"
#include "../core/color.hpp"
#include "hooray/render/drawcommands.hpp"

namespace hooray {
    class Image2D : public Node2D {
    public:
        ~Image2D() override = default;

        void set_texture_id(std::string id) {
            texture_id_ = std::move(id);
        }

        [[nodiscard]] const std::string &get_texture_id() const {
            return texture_id_;
        }

        void set_tint(const Color &color) {
            tint_ = color;
        }

        [[nodiscard]] Color get_tint() const {
            return tint_;
        }

    protected:
        void on_init(const AssetManager &assets) override {
            texture_ = assets.get_texture(texture_id_);
        }

        void on_draw(RenderCommandList &cmds) override {
            if (!texture_ || !texture_->is_valid()) return;

            const auto &handle = texture_->handle();
            const auto width = static_cast<float>(handle.width);
            const auto height = static_cast<float>(handle.height);

            cmds.emplace<PushTransformCmd>(PushTransformCmd{.transform = transform});
            cmds.emplace<DrawTextureCmd>(DrawTextureCmd{
                .texture = handle,
                .source = {.x = 0.0f, .y = 0.0f, .width = width, .height = height},
                .dest = {.x = 0.0f, .y = 0.0f, .width = width, .height = height},
                .origin = transform.origin,
                .rotation = 0.0f,
                .tint = tint_
            });
            cmds.emplace<PopTransformCmd>();
        }

    private:
        std::string texture_id_;
        const Texture *texture_{nullptr};
        Color tint_{colors::WHITE};
    };
}
