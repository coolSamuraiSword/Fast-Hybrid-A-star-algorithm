#include "mini_test.h"
#include "windowed_fqueue.hpp"

using namespace mini_test;
using hybrid_a_star::frontier::WindowedFQueue;

TEST(BasicAssertions) {
    EXPECT_TRUE(true);
    EXPECT_EQ(1, 1);
}

TEST(WindowedFQueueOrdering) {
    WindowedFQueue<int> q(1.0);
    q.push(1, 0.2); // bucket 0
    q.push(2, 0.2); // tie, later sequence
    q.push(3, 0.1); // smaller f in same bucket

    EXPECT_EQ(q.size(), 3u);
    EXPECT_EQ(q.pop_min().value(), 3);
    EXPECT_EQ(q.pop_min().value(), 1);
    EXPECT_EQ(q.pop_min().value(), 2);
    EXPECT_TRUE(q.empty());
}
