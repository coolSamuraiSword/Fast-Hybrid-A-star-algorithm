#pragma once

#include <vector>

namespace hybrid_a_star {

// Basic vehicle state
struct State {
    double x{};    ///< position x
    double y{};    ///< position y
    double theta{};///< heading angle
};

// Placeholder for motion primitive description
struct MotionPrimitive {
    // TODO: define fields describing motion primitives
};

// Successor generation from (x, y, theta) using motion primitives
// std::vector<State> generateSuccessors(const State& current,
//                                       const std::vector<MotionPrimitive>& primitives);

// Collision checking interface
// bool isCollisionFree(const State& state);

// Admissible heuristic selection (Euclidean / Dubins / RS)
// double heuristic(const State& from, const State& to);

// Analytic expansion toggle
// bool allowAnalyticExpansion();

} // namespace hybrid_a_star

