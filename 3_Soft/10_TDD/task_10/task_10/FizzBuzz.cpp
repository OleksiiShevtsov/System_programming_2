#include <gmock/gmock.h>
#include <gtest/gtest.h>//можно не писать если есть gmock
#include <string>
#include <sstream>

/*
Функция должна напечатать от 1 до 100
Если число делиться на 3 - выводим Fizz
Если число делиться на 5 - выводим Buzz
Если число делиться на 15 - выводим FizzBuzz
*/

std::string getNumber(int i) {

	std::string ret;

	if (i % 3 == 0) {
		ret += "Fizz";
	}
	if (i % 5 == 0) {
		ret += "Buzz";
	}
	return ret.empty() ? std::to_string(i) : ret;
}

void printNumbers( std::ostream& stream) {
	for (int i = 1; i <= 100; i++) {
		stream << getNumber(i) << std::endl;
	}
}

TEST(GetNumberTest, GetNumberReturnsTwoForTwo) {
	EXPECT_EQ(getNumber(2), "2");
}

TEST(GetNumberTest, GetNumberReturnsFizzForMultipleOf3) {
	EXPECT_EQ(getNumber(3), "Fizz");
}

TEST(GetNumberTest, GetNumberReturnsFizzForMultipleOf9and12) {
	EXPECT_EQ(getNumber(9), "Fizz");
	EXPECT_EQ(getNumber(12), "Fizz");
}

TEST(GetNumberTest, GetNumberReturnsBuzzForMultipleOf5) {
	EXPECT_EQ(getNumber(5), "Buzz");
}

TEST(GetNumberTest, GetNumberReturnsBuzzForMultipleOf10and20) {
	EXPECT_EQ(getNumber(10), "Buzz");
	EXPECT_EQ(getNumber(20), "Buzz");
}

TEST(GetNumberTest, GetNumberReturnsBuzzForMultipleOf15) {
	EXPECT_EQ(getNumber(15), "FizzBuzz");
	EXPECT_EQ(getNumber(30), "FizzBuzz");
}

TEST(PrintNumbersTest, PrintNumbersPrintsExpectedString)
{
	std::stringstream ss;
	printNumbers(ss);
	std::string res;
	res.resize(58);
	ss.read(const_cast<char*>(res.c_str()), 58);
	std::string expected = R"(1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
)";
	EXPECT_EQ(res, expected);
}