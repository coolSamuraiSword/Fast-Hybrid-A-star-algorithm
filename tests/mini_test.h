#pragma once
#include <functional>
#include <iostream>
#include <vector>

namespace mini_test {
using test_func = std::function<void()>;

inline std::vector<test_func>& registry() {
    static std::vector<test_func> tests;
    return tests;
}

struct registrar {
    registrar(test_func fn) { registry().push_back(fn); }
};

#define TEST(name) \
    void name(); \
    static ::mini_test::registrar registrar_##name(name); \
    void name()

inline int failures = 0;

#define EXPECT_TRUE(cond)                                                       \
    do {                                                                        \
        if (!(cond)) {                                                          \
            std::cerr << __FILE__ << ":" << __LINE__                            \
                      << " EXPECT_TRUE(" #cond ") failed\n";                    \
            ++::mini_test::failures;                                            \
        }                                                                       \
    } while (0)

#define EXPECT_EQ(a, b)                                                         \
    do {                                                                        \
        if (!((a) == (b))) {                                                    \
            std::cerr << __FILE__ << ":" << __LINE__                            \
                      << " EXPECT_EQ(" #a ", " #b ") failed: " << (a)           \
                      << " != " << (b) << "\n";                                 \
            ++::mini_test::failures;                                            \
        }                                                                       \
    } while (0)

} // namespace mini_test

int main() {
    for (auto& t : mini_test::registry()) t();
    if (mini_test::failures) {
        std::cerr << mini_test::failures << " test(s) failed\n";
        return 1;
    }
    std::cout << "All tests passed\n";
    return 0;
}
