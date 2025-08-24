#include "mini_test.h"

#include "bucket_heap.hpp"

using namespace hybrid_a_star::frontier;
using namespace mini_test;

TEST(BucketHeapOrder) {
    BucketHeap<int> bh(1.0, 8);
    bh.push(1, 3.0);
    bh.push(2, 1.0);
    bh.push(3, 2.0);

    auto a = bh.pop_min();
    auto b = bh.pop_min();
    auto c = bh.pop_min();

    EXPECT_TRUE(a.has_value());
    EXPECT_TRUE(b.has_value());
    EXPECT_TRUE(c.has_value());
    EXPECT_EQ(a.value(), 2);
    EXPECT_EQ(b.value(), 3);
    EXPECT_EQ(c.value(), 1);
    EXPECT_TRUE(bh.empty());
}

TEST(BucketHeapTie) {
    BucketHeap<int> bh(1.0, 4);
    bh.push(1, 1.0);
    bh.push(2, 1.0);
    auto a = bh.pop_min();
    auto b = bh.pop_min();
    EXPECT_TRUE(a.has_value());
    EXPECT_TRUE(b.has_value());
    EXPECT_EQ(a.value(), 1);
    EXPECT_EQ(b.value(), 2);
}

TEST(BucketHeapNegative) {
    BucketHeap<int> bh(1.0, 4);
    bh.push(1, -0.5);
    bh.push(2, 0.2);
    auto a = bh.pop_min();
    EXPECT_TRUE(a.has_value());
    EXPECT_EQ(a.value(), 1);
}

