#pragma once

#include "frontier.hpp"

#include <cmath>
#include <cstddef>
#include <deque>
#include <limits>
#include <vector>

namespace hybrid_a_star::frontier {

/**
 * @brief Ring-of-buckets frontier for bounded-suboptimal search (e.g. Weighted A*).
 *
 * The container discretises the f-cost space into @p K buckets of width
 * @p delta and stores entries in the corresponding bucket.  Buckets are scanned
 * in a cyclic manner, providing \f$O(1)\f$ amortised insertion while
 * maintaining an approximate ordering on the f-cost.  The structure does *not*
 * provide a strict total order; for exact optimality use WindowedFQueue or a
 * binary heap instead.  For bounded-suboptimal Weighted A* choose @p delta
 * relative to the minimum edge cost and the heuristic weight.
 *
 * @tparam Entry payload type representing a search node.
 */
template <typename Entry>
class BucketHeap : public IFrontier<Entry> {
public:
    /**
     * @brief Construct a bucket heap.
     *
     * @param delta Width of each bucket.
     * @param K Number of buckets in the ring.
     */
    BucketHeap(double delta, std::size_t K)
        : delta_(delta),
          K_(K),
          buckets_(K),
          sz_(0),
          min_idx_(0),
          min_f_(std::numeric_limits<double>::infinity()),
          seq_(0) {}

    void push(const Entry& e, double f) override {
        const std::size_t idx = bucket_index(f);
        buckets_[idx].push_back({{f, e}, seq_++});
        ++sz_;
        if (f < min_f_) {
            min_f_ = f;
            min_idx_ = idx;
        }
    }

    std::optional<Entry> pop_min() override {
        if (sz_ == 0) return std::nullopt;

        for (std::size_t off = 0; off < K_; ++off) {
            const std::size_t idx = (min_idx_ + off) % K_;
            auto& bucket = buckets_[idx];
            if (!bucket.empty()) {
                std::size_t best = 0;
                double best_f = bucket[0].item.f;
                std::size_t best_seq = bucket[0].seq;
                for (std::size_t i = 1; i < bucket.size(); ++i) {
                    const auto& cand = bucket[i];
                    if (cand.item.f < best_f ||
                        (cand.item.f == best_f && cand.seq < best_seq)) {
                        best = i;
                        best_f = cand.item.f;
                        best_seq = cand.seq;
                    }
                }

                FrontierItem<Entry> fi = bucket[best].item;
                bucket.erase(bucket.begin() + static_cast<long long>(best));
                --sz_;
                min_idx_ = idx;
                min_f_ = fi.f;
                return fi.payload;
            }
        }

        // Inconsistent size accounting; reset.
        sz_ = 0;
        min_f_ = std::numeric_limits<double>::infinity();
        return std::nullopt;
    }

    [[nodiscard]] bool empty() const override { return sz_ == 0; }

    [[nodiscard]] std::size_t size() const override { return sz_; }

private:
    struct Node {
        FrontierItem<Entry> item;
        std::size_t seq;
    };

    [[nodiscard]] std::size_t bucket_index(double f) const {
        long long q = static_cast<long long>(std::floor(f / delta_));
        long long m = static_cast<long long>(K_);
        long long r = q % m;
        if (r < 0) r += m;
        return static_cast<std::size_t>(r);
    }

    double delta_;
    std::size_t K_;
    std::vector<std::deque<Node>> buckets_;
    std::size_t sz_;
    std::size_t min_idx_;
    double min_f_;
    std::size_t seq_;
};

} // namespace hybrid_a_star::frontier

