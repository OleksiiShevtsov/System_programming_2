#include <gmock/gmock.h>
#include <string>
#include <sstream>
#include <cmath>

int decimalRepresentation(std::string ternaryRepresentation) {
	int ternaryNumber{ std::stoi(ternaryRepresentation) };
	int decimalNumber{ 0 };
	for (int i = 0; ternaryNumber != 0; i++){
		decimalNumber += (ternaryNumber % 10) * pow(3, i);
		ternaryNumber /= 10;
	}
	return decimalNumber;
}

TEST(DecimalRepresentationTest, TestForSingleDigits) {
	EXPECT_EQ(decimalRepresentation("20"), 6);
	EXPECT_EQ(decimalRepresentation("100"), 9);
}

TEST(DecimalRepresentationTest, TestforTwoDigitNumbers) {
	EXPECT_EQ(decimalRepresentation("110"), 12);
	EXPECT_EQ(decimalRepresentation("122"), 17);
}

TEST(DecimalRepresentationTest, TestforThreeDigitNumbers) {
	EXPECT_EQ(decimalRepresentation("102012"), 302);
	EXPECT_EQ(decimalRepresentation("1101000"), 999);
}

TEST(DecimalRepresentationTest, TestforFourDigitNumbers) {
	EXPECT_EQ(decimalRepresentation("2202212"), 2021);
	EXPECT_EQ(decimalRepresentation("2201221"), 1996);
}