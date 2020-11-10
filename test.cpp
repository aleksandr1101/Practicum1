#include <gtest/gtest.h>
#include "solve.h"

TEST(EasyestTest, TestingOnlyMul) {
	EXPECT_EQ(4, solve("baac...", 'a', 2));
}

TEST(GreaterTest, TestingMulAndSum) {
	EXPECT_EQ(4, solve("baac...caaab....+", 'a', 2));
	EXPECT_EQ(INF, solve("baac...caaab....+", 'a', 4));
}

TEST(Samples, TestsFromSamples) {
	EXPECT_EQ(4, solve("ab+c.aba.*.bac.+.+*", 'b', 2));
	EXPECT_EQ(7, solve("acb..bab.c.*.ab.ba.+.+*a.", 'b', 3));
}

TEST(DifficultTest, TestingKlini) {
    EXPECT_EQ(9, solve("bbaaaaaaacc..........ab.ba.aaaaa....++*+", 'a', 7));
}