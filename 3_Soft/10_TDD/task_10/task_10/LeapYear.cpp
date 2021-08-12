#include <gtest/gtest.h>
#include <string>
#include <sstream>

/*
Проверка высокосного года
Если год /4 выс.
Если год /100 не выс.
Если год /400 выс.
остальные не выс.
*/

bool isLeapYear(int year) {
	if (year % 400 == 0) {
		return true;
	}
	if (year % 100 == 0) {
		return false;
	}
	if (year % 4 == 0) {
		return true;
	}
	return false;
}

TEST(IsLeapYearTest, ReturnsLeapYearFor2004) {
	EXPECT_EQ(isLeapYear(2004), true);
	EXPECT_EQ(isLeapYear(2108), true);
	EXPECT_EQ(isLeapYear(2116), true);
	EXPECT_EQ(isLeapYear(1120), true);
}

TEST(IsLeapYearTest, ReturnsLeapYearFor2100) {
	EXPECT_EQ(isLeapYear(2100), false);
	EXPECT_EQ(isLeapYear(1400), false);
	EXPECT_EQ(isLeapYear(1100), false);
	EXPECT_EQ(isLeapYear(1800), false);
}

TEST(IsLeapYearTest, ReturnsLeapYearFor2400) {
	EXPECT_EQ(isLeapYear(2400), true);
	EXPECT_EQ(isLeapYear(2000), true);
	EXPECT_EQ(isLeapYear(1600), true);
	EXPECT_EQ(isLeapYear(1200), true);
}

TEST(IsLeapYearTest, ReturnsLeapYearForElse) {
	EXPECT_EQ(isLeapYear(1111), false);
	EXPECT_EQ(isLeapYear(2021), false);
	EXPECT_EQ(isLeapYear(2007), false);
	EXPECT_EQ(isLeapYear(2015), false);
}

