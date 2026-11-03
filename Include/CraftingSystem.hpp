#pragma once
#include <iostream>
#include <string_view>
#include <array>

class CraftingSystem {
public:
    struct Affix {
        std::string_view name;
        int value;
    };

    // Zero-allocation deterministic crafting affix rolling using static lookup tables
    Affix rollAffix(unsigned int seed) {
        static constexpr std::array<Affix, 4> affixPool = {{
            {"Vanguard's Glacial Resilience", +45},
            {"Void-Scarred Critical Striking", +18},
            {"Thermal-Core Heat Dissipation", +30},
            {"Stellar Siphon Mana Recovery", +12}
        }};

        size_t index = seed % affixPool.size();
        return affixPool[index];
    }
};