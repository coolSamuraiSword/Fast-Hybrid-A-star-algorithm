#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace hybrid_a_star::frontier {

/**
 * @brief Interface for A*/Hybrid A* frontier containers.
 *
 * The frontier stores candidate nodes ordered by their estimated total cost
 * \f$f\f$.  Stale entries created by the lack of decrease-key support must be
 * filtered by the planner (lazy decrease-key).
 *
 * @tparam Entry payload type representing a search node.
 */
template <typename Entry>
class IFrontier {
public:
    /// Virtual destructor for safe polymorphic destruction.
    virtual ~IFrontier() = default;

    /**
     * @brief Insert an entry into the frontier.
     *
     * @param e payload to insert.
     * @param f priority key; smaller values are popped first.
     */
    virtual void push(const Entry& e, double f) = 0;

    /**
     * @brief Remove and return the entry with the smallest priority.
     *
     * The caller is responsible for discarding stale entries.
     */
    virtual std::optional<Entry> pop_min() = 0;

    /// @return true if the frontier holds no elements.
    [[nodiscard]] virtual bool empty() const = 0;

    /// @return number of elements currently stored in the frontier.
    [[nodiscard]] virtual std::size_t size() const = 0;
};

/**
 * @brief Convenience item representing a node in a frontier.
 */
template <typename Entry>
struct FrontierItem {
    double f;      ///< priority key
    Entry payload; ///< payload associated with the key

    constexpr FrontierItem(double f_, Entry payload_)
        : f(f_), payload(std::move(payload_)) {}
};

/**
 * @brief Comparator for FrontierItem enabling min-heap structures.
 */
template <typename Entry>
struct FrontierItemCompare {
    constexpr bool operator()(const FrontierItem<Entry>& lhs,
                              const FrontierItem<Entry>& rhs) const noexcept {
        return lhs.f > rhs.f;
    }
};

} // namespace hybrid_a_star::frontier

