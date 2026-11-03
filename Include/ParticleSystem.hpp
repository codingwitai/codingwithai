#pragma once
#include <iostream>
#include <array>
#include <cstddef>

struct Particle {
    float x = 0.0f;
    float y = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    float lifetime = 0.0f;
    bool active = false;
};

class ParticleSystem {
public:
    static constexpr size_t MAX_PARTICLES = 1024;

    // Emits a particle by re-using an inactive slot in the static pool
    void spawn(float x, float y, float vx, float vy, float lifetime) {
        for (auto& p : m_pool) {
            if (!p.active) {
                p.x = x;
                p.y = y;
                p.vx = vx;
                p.vy = vy;
                p.lifetime = lifetime;
                p.active = true;
                return; // Re-used existing memory pool slot cleanly
            }
        }
    }

    // Updates particle physics and recycles expired particles without heap activity
    void update(float dt) {
        m_activeCount = 0;
        for (auto& p : m_pool) {
            if (p.active) {
                p.x += p.vx * dt;
                p.y += p.vy * dt;
                p.lifetime -= dt;

                if (p.lifetime <= 0.0f) {
                    p.active = false;
                } else {
                    ++m_activeCount;
                }
            }
        }
    }

    size_t getActiveCount() const { return m_activeCount; }

private:
    std::array<Particle, MAX_PARTICLES> m_pool{};
    size_t m_activeCount = 0;
};