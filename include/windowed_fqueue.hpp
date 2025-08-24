#pragma once

#include "frontier.hpp"

#include <cmath>
#include <cstddef>
#include <deque>
#include <iterator>
#include <map>
#include <optional>
#include <utility>

namespace hybrid_a_star::frontier {

/**
 * @brief Partial-order sliding window frontier (PO-HA* variant).
 *
 * Entries are grouped into buckets of width \f$\delta\f$ indexed by
 * \f$\lfloor f/\delta \rfloor\f$.  Within the current minimum bucket the
 * item with the smallest \f$f\f$ is returned, ties broken deterministically
 * by insertion order.
 *
 * When the window width satisfies the lemma condition \f$\delta \leq c_{\min}\f$
 * and the heuristic \f$h\f$ is consistent, this frontier preserves the optimal
 * expansion order of a full priority queue while avoiding decrease-key.
 *
 * @tparam Entry payload type representing a search node.
 */
template <typename Entry>
class WindowedFQueue final : public IFrontier<Entry> {
public:
    /// Create a frontier with bucket width @p delta.
    explicit WindowedFQueue(double delta) : delta_(delta) {}

    void push(const Entry& e, double f) override {
        const int idx = static_cast<int>(std::floor(f / delta_));
        auto& bucket = buckets_[idx];
        bucket.emplace_back(f, seq_, e);
        ++seq_;
        if (sz_ == 0 || idx < min_idx_) min_idx_ = idx;
        ++sz_;
    }

    std::optional<Entry> pop_min() override {
        if (sz_ == 0) return std::nullopt;

        auto it = buckets_.find(min_idx_);
        if (it == buckets_.end()) {
            it = buckets_.lower_bound(min_idx_);
            if (it == buckets_.end()) return std::nullopt;
            min_idx_ = it->first;
        }

        auto& dq = it->second;
        auto best = dq.begin();
        for (auto iter = std::next(dq.begin()); iter != dq.end(); ++iter) {
            if (iter->f < best->f ||
                (iter->f == best->f && iter->seq < best->seq)) {
                best = iter;
            }
        }

        Entry result = std::move(best->payload);
        dq.erase(best);
        --sz_;

        if (dq.empty()) {
            auto next = buckets_.erase(it); // returns iterator to next bucket
            if (next != buckets_.end()) {
                min_idx_ = next->first;
            }
        }

        return result;
    }

    [[nodiscard]] bool empty() const override { return sz_ == 0; }

    [[nodiscard]] std::size_t size() const override { return sz_; }

private:
    struct BucketItem {
        double f;
        std::size_t seq;
        Entry payload;
        BucketItem(double f_, std::size_t seq_, const Entry& payload_)
            : f(f_), seq(seq_), payload(payload_) {}
    };

    double delta_;
    std::map<int, std::deque<BucketItem>> buckets_;
    int min_idx_ = 0;         // index of current minimum non-empty bucket
    std::size_t sz_ = 0;      // total number of stored elements
    std::size_t seq_ = 0;     // sequence counter for deterministic tie-breaking
};

} // namespace hybrid_a_star::frontier

