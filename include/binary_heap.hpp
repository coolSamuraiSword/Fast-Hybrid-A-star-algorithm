#pragma once

#include <cstddef>
#include <cstdint>
#include <queue>
#include <vector>

#include "frontier.hpp"

namespace hybrid_a_star::frontier {

/**
 * \brief Binary heap based frontier implemented with std::priority_queue.
 *
 * Maintains a min-queue ordered by the f-cost of entries. When multiple
 * entries share the same f value, insertion order determines priority to
 * guarantee deterministic behavior in unit tests.
 *
 * @tparam Entry Type stored in the frontier. Must expose a member `f`
 *               representing its total estimated cost.
 */
template <typename Entry>
class BinaryHeap : public IFrontier<Entry> {
private:
    struct FrontierItem {
        Entry entry;
        std::uint64_t seq;
        double f;
        FrontierItem(const Entry& e, std::uint64_t s) : entry(e), seq(s), f(e.f) {}
    };

    struct Compare {
        bool operator()(const FrontierItem& lhs, const FrontierItem& rhs) const noexcept {
            if (lhs.f == rhs.f) {
                return lhs.seq > rhs.seq; // smaller sequence first
            }
            return lhs.f > rhs.f; // min-queue by f
        }
    };

    std::priority_queue<FrontierItem, std::vector<FrontierItem>, Compare> pq_;
    std::uint64_t next_seq_ = 0;

public:
    /**
     * \brief Insert an entry into the frontier.
     *\n Complexity: O(log n)
     */
    void push(const Entry& e) override { pq_.emplace(e, next_seq_++); }

    /**
     * \brief Remove and return the minimal f-cost entry.
     *\n Complexity: O(log n)
     */
    Entry pop_min() override {
        FrontierItem top = pq_.top();
        pq_.pop();
        return top.entry;
    }

    /**
     * \brief Check whether the frontier contains no elements.
     *\n Complexity: O(1)
     */
    bool empty() const noexcept override { return pq_.empty(); }

    /**
     * \brief Return the number of stored entries.
     *\n Complexity: O(1)
     */
    std::size_t size() const noexcept override { return pq_.size(); }
};

} // namespace hybrid_a_star::frontier

