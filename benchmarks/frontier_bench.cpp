#include "frontier.hpp"
#include <chrono>
#include <iostream>

using namespace hybrid_a_star::frontier;

int main() {
    Frontier f;
    auto start = std::chrono::steady_clock::now();
    f.touch();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Frontier bench elapsed: " << elapsed.count() << "s\n";
    return 0;
}
