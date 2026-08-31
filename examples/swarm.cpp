#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <ranges>
#include <numbers>

#include "hooray.hpp"

namespace {

    struct Particle {
        float angle;
        float orbitRadius;
        float speed;
        float size;
        Hooray::Color baseColor;
        float offsetY;
        bool isColliding{false};
        float x{0.0f};
        float y{0.0f};
        Hooray::Circle circle;
    };

    struct Ring {
        float radius;
        float maxRadius;
        float speed;
    };

    class NeonSwarmApp : public Hooray::Application {
    private:
        static constexpr int NUM_PARTICLES = 250;
        float width_f = 900.0f;
        float height_f = 700.0f;
        float centerX = width_f / 2.0f;
        float centerY = height_f / 2.0f;

        float time_{0.0f};
        std::vector<Particle> particles;
        std::vector<Ring> rings;

        static float randomFloat(const float min, const float max) {
            thread_local std::mt19937 generator(std::random_device{}());
            std::uniform_real_distribution distribution(min, max);
            return distribution(generator);
        }

    public:
        NeonSwarmApp() : Hooray::Application(900, 700, "2D Orbiting Neon Swarm") {}

        void on_init() override {
            // Initialize particles
            particles.reserve(NUM_PARTICLES);
            for (int i = 0; i < NUM_PARTICLES; ++i) {
                Particle p;
                p.angle = randomFloat(0.0f, 2.0f * std::numbers::pi);
                p.orbitRadius = 40.0f + randomFloat(0.0f, 260.0f);
                p.speed = (randomFloat(0.0f, 1.0f) - 0.5f) * 0.04f;
                p.size = 2.0f + randomFloat(0.0f, 6.0f);
                p.baseColor = (i % 2 == 0) ? Hooray::Palette::ElectricBlue : Hooray::Palette::HotPink;
                p.offsetY = (randomFloat(0.0f, 1.0f) - 0.5f) * 50.0f;
                particles.push_back(p);
            }

            // Initialize background rings
            rings.reserve(5);
            for (int i = 0; i < 5; ++i) {
                rings.push_back({
                    static_cast<float>(i * 60),
                    300.0f,
                    30.0f + randomFloat(0.0f, 20.0f)
                });
            }
        }

        void on_update(float delta_time) override {
            time_ += delta_time;

            // Rotate orbiting shapes and update current positions
            for (auto& p : particles) {
                p.angle += p.speed;
                p.x = centerX + std::cos(p.angle) * p.orbitRadius;
                p.y = centerY + std::sin(p.angle) * p.orbitRadius + std::sin(time_ * 2.0f + p.angle + p.offsetY) * 15.0f;
                p.circle = Hooray::Circle(p.x, p.y, p.size);
                p.isColliding = false;
            }

            // Circle collision checking
            for (size_t i = 0; i < particles.size(); ++i) {
                for (size_t j = i + 1; j < particles.size(); ++j) {
                    if (particles[i].circle.overlaps(particles[j].circle)) {
                        particles[i].isColliding = true;
                        particles[j].isColliding = true;
                    }
                }
            }

            // Expand background rings
            for (auto& r : rings) {
                r.radius += r.speed * delta_time;
                if (r.radius > r.maxRadius) {
                    r.radius = 0.0f;
                }
            }
        }

        void on_draw(Hooray::Renderer& render) override {
            render.clear_background(Hooray::Palette::CharBlack);

            // Standard screen-space rendering context via Layer2d
            constexpr Hooray::Camera2D default_camera{
                .offset = {0.0f, 0.0f},
                .target = {0.0f, 0.0f},
                .rotation = 0.0f,
                .zoom = 1.0f
            };

            render.with_layer_2d(default_camera, [this](Hooray::Layer2d layer) {

                // 1. Draw animated expanding geometric rings
                for (const auto& r : rings) {
                    const float alpha = 1.0f - (r.radius / r.maxRadius);
                    Hooray::Color ringColor = Hooray::Palette::Purple.get_alpha(alpha * 0.4f);
                    layer.draw_circle(Hooray::Vector2(centerX, centerY), r.radius, ringColor);
                }

                // 2. Draw rotating center diamond structure
                const float diamondSize = 35.0f + std::sin(time_ * 3.0f) * 10.0f;
                const float lerpFactorCore = (std::sin(time_ * 2.0f) + 1.0f) / 2.0f;
                const Hooray::Color coreColor = Hooray::Palette::Cyan.get_lerp(Hooray::Palette::Magenta, lerpFactorCore);

                Hooray::Rectangle diamondRect(
                    centerX - diamondSize / 2.0f,
                    centerY - diamondSize / 2.0f,
                    diamondSize,
                    diamondSize
                );
                layer.draw_rectangle(diamondRect, coreColor);

                // 3. Draw orbiting particle cloud
                for (const auto& p : particles) {
                    Hooray::Color particleColor;
                    if (p.isColliding) {
                        particleColor = Hooray::Palette::Copper;
                    } else {
                        float lerpFactor = (std::sin(time_ + p.angle) + 1.0f) / 2.0f;
                        particleColor = p.baseColor.get_lerp(Hooray::Palette::Yellow, lerpFactor);
                    }

                    // Main particle shape
                    layer.draw_circle(Hooray::Vector2(p.x, p.y), p.size, particleColor);

                    // Outer ambient glow circle
                    layer.draw_circle(Hooray::Vector2(p.x, p.y), p.size * 2.0f, particleColor.get_alpha(0.25f));
                }

                // 4. Draw vibrant connecting line pulses
                if (!particles.empty()) {
                    int lineCount = std::min(12, static_cast<int>(particles.size()));
                    int step = particles.size() / lineCount;
                    int offset = std::max(1, static_cast<int>(particles.size() * 0.15f));

                    for (int i = 0; i < lineCount; ++i) {
                        int idx1 = (i * step) % particles.size();
                        int idx2 = (idx1 + offset) % particles.size();

                        const auto& p1 = particles[idx1];
                        const auto& p2 = particles[idx2];

                        layer.draw_line(
                            Hooray::Vector2(p1.x, p1.y),
                            Hooray::Vector2(p2.x, p2.y),
                            1.0f, // Line thickness parameter required by C++ Layer2d API
                            Hooray::Palette::Lime.get_alpha(0.2f)
                        );
                    }
                }
            });
        }
    };
}

int main() {
    NeonSwarmApp app;
    app.run();
    return 0;
}