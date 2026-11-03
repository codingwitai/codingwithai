#pragma once
#include <iostream>
#include <string_view>

class WeatherSystem {
public:
    enum class Type { Clear, Blizzard, ThermalHazard, VoidStorm };

    void update(float dt) {
        // Zero-allocation deterministic state update
        m_timer += dt;
        if (m_timer > 10.0f) {
            m_currentType = static_cast<Type>((static_cast<int>(m_currentType) + 1) % 4);
            m_timer = 0.0f;
        }
    }

    std::string_view getCurrentWeatherName() const {
        switch (m_currentType) {
            case Type::Clear: return "Clear Skies (Stable)";
            case Type::Blizzard: return "Blizzard Density High (-10% Speed)";
            case Type::ThermalHazard: return "Thermal-Core Venting (Heat Debuff)";
            case Type::VoidStorm: return "Void-Scarred Peak Anomaly";
        }
        return "Unknown";
    }

private:
    Type m_currentType = Type::Blizzard;
    float m_timer = 0.0f;
};