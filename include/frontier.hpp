#pragma once

#include <cstddef>

namespace hybrid_a_star::frontier {

/**
 * \brief Interface for frontier data structures used in search algorithms.
 *
 * @tparam Entry Type stored in the frontier.
 */
template <typename Entry>
class IFrontier {
public:
    virtual ~IFrontier() = default;

    /**
     * \brief Insert an entry into the frontier.
     *\n Complexity: O(log n)
     */
    virtual void push(const Entry& e) = 0;

    /**
     * \brief Remove and return the minimal f-cost entry.
     *\n Complexity: O(log n)
     */
    virtual Entry pop_min() = 0;

    /**
     * \brief Check whether the frontier contains no elements.
     *\n Complexity: O(1)
     */
    virtual bool empty() const noexcept = 0;

    /**
     * \brief Return the number of stored entries.
     *\n Complexity: O(1)
     */
    virtual std::size_t size() const noexcept = 0;
};

} // namespace hybrid_a_star::frontier

