#pragma once
#include <iostream>
#include <array>
#include <string_view>
#include <atomic>

struct AssetRequest {
    std::string_view path;
    bool loaded = false;
    bool inUse = false;
};

class AsyncAssetQueue {
public:
    static constexpr size_t QUEUE_CAPACITY = 64;

    // Enqueues an asset request into the pre-allocated static buffer
    bool requestLoad(std::string_view path) {
        for (auto& req : m_requests) {
            if (!req.inUse) {
                req.path = path;
                req.loaded = false;
                req.inUse = true;
                m_pendingCount.fetch_add(1, std::memory_order_relaxed);
                return true;
            }
        }
        return false; // Queue full, zero heap allocation fallback
    }

    // Simulates background worker thread processing with zero allocations
    void processBackgroundWorkerMock() {
        for (auto& req : m_requests) {
            if (req.inUse && !req.loaded) {
                req.loaded = true;
                m_pendingCount.fetch_sub(1, std::memory_order_relaxed);
            }
        }
    }

    size_t getPendingCount() const {
        return m_pendingCount.load(std::memory_order_relaxed);
    }

private:
    std::array<AssetRequest, QUEUE_CAPACITY> m_requests{};
    std::atomic<size_t> m_pendingCount{0};
};