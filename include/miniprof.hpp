#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

namespace miniprof {

inline std::uint64_t now_ns() {
    return static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch())
            .count());
}

class ScopedTimer {
public:
    explicit ScopedTimer(const std::string& label, std::ostream& os = std::cerr)
        : label_(label), os_(os), start_(now_ns()), active_(true) {}

    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

    ScopedTimer(ScopedTimer&& other) noexcept
        : label_(other.label_), os_(other.os_), start_(other.start_),
          active_(other.active_) {
        other.active_ = false;
    }

    ScopedTimer& operator=(ScopedTimer&& other) noexcept {
        if (this != &other) {
            if (active_) {
                const auto end = now_ns();
                const double ms =
                    static_cast<double>(end - start_) / 1'000'000.0;
                os_ << label_ << ": " << ms << " ms" << std::endl;
            }
            label_ = other.label_;
            os_ = other.os_;
            start_ = other.start_;
            active_ = other.active_;
            other.active_ = false;
        }
        return *this;
    }

    ~ScopedTimer() {
        if (active_) {
            const auto end = now_ns();
            const double ms =
                static_cast<double>(end - start_) / 1'000'000.0;
            os_ << label_ << ": " << ms << " ms" << std::endl;
        }
    }

private:
    std::string label_;
    std::ostream& os_;
    std::uint64_t start_;
    bool active_;
};

} // namespace miniprof

