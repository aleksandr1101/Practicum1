#include <gtest/gtest.h>
#include "solve.h"

TEST(OnlyMulTest, OnlyMul) {
	EXPECT_EQ(4, solve("baac...", 'a', 2));
}

TEST(MulAndSumTest, MulAndSumTest) {
	EXPECT_EQ(4, solve("baac...caaab....+", 'a', 2));
	EXPECT_EQ(INF, solve("baac...caaab....+", 'a', 4));
}

TEST(Samples, Samples) {
	EXPECT_EQ(4, solve("ab+c.aba.*.bac.+.+*", 'b', 2));
	EXPECT_EQ(7, solve("acb..bab.c.*.ab.ba.+.+*a.", 'b', 3));
}