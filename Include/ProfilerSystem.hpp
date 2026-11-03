#pragma once
#include <iostream>
#include <array>
#include <cstddef>

class ProfilerSystem {
public:
    struct FrameMetric {
        float frameTimeMs;
        bool zeroAllocEnforced;
    };

    static constexpr size_t MAX_SAMPLES = 300;

    void recordFrame(float frameTimeMs, bool zeroAlloc) {
        if (m_sampleCount < MAX_SAMPLES) {
            m_samples[m_sampleCount++] = {frameTimeMs, zeroAlloc};
        } else {
            m_samples[m_currentIndex] = {frameTimeMs, zeroAlloc};
            m_currentIndex = (m_currentIndex + 1) % MAX_SAMPLES;
        }
    }

    float getAverageFrameTime() const {
        if (m_sampleCount == 0) return 0.0f;
        float total = 0.0f;
        size_t count = (m_sampleCount < MAX_SAMPLES) ? m_sampleCount : MAX_SAMPLES;
        for (size_t i = 0; i < count; ++i) {
            total += m_samples[i].frameTimeMs;
        }
        return total / static_cast<float>(count);
    }

    size_t getSampleCount() const { return m_sampleCount; }

private:
    std::array<FrameMetric, MAX_SAMPLES> m_samples{};
    size_t m_sampleCount = 0;
    size_t m_currentIndex = 0;
};