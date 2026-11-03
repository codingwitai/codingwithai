#pragma once
#include <iostream>
#include <array>
#include <string_view>

struct CombatTextNode {
    std::string_view text;
    float x = 0.0f;
    float y = 0.0f;
    float lifetime = 0.0f;
    bool active = false;
};

class CombatTextSystem {
public:
    static constexpr size_t MAX_TEXT_NODES = 256;

    void spawnText(std::string_view text, float x, float y, float lifetime) {
        for (auto& node : m_pool) {
            if (!node.active) {
                node.text = text;
                node.x = x;
                node.y = y;
                node.lifetime = lifetime;
                node.active = true;
                return;
            }
        }
    }

    void update(float dt) {
        for (auto& node : m_pool) {
            if (node.active) {
                node.y += 20.0f * dt; // Float upward
                node.lifetime -= dt;
                if (node.lifetime <= 0.0f) {
                    node.active = false;
                }
            }
        }
    }

private:
    std::array<CombatTextNode, MAX_TEXT_NODES> m_pool{};
};