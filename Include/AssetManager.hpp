#pragma once
#include <iostream>
#include <array>
#include <string_view>

struct AssetMetadata {
    std::string_view name;
    size_t sizeBytes;
    bool cached;
};

class AssetManager {
public:
    static constexpr size_t MAX_CACHE_SLOTS = 32;

    bool registerAsset(std::string_view name, size_t sizeBytes) {
        for (auto& slot : m_cache) {
            if (!slot.cached) {
                slot.name = name;
                slot.sizeBytes = sizeBytes;
                slot.cached = true;
                return true;
            }
        }
        return false; // Cache full, zero heap allocation enforcement
    }

    bool isCached(std::string_view name) const {
        for (const auto& slot : m_cache) {
            if (slot.cached && slot.name == name) {
                return true;
            }
        }
        return false;
    }

private:
    std::array<AssetMetadata, MAX_CACHE_SLOTS> m_cache{};
};