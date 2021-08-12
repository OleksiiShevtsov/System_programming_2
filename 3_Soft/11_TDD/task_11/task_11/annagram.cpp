#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <string>
#include <vector>

const std::vector<std::string> GetAnagrams(const std::string& compare_with, 
	const std::vector<std::string>& words) {
	
	std::vector<std::string> ret;
	if (!words.empty()) {

		std::string compare(compare_with);
		std::sort(compare.begin(), compare.end());
		std::transform(compare.begin(), compare.end(), compare.begin(), tolower);
		
		for (const auto& word : words) {
			
			auto sorted_word = word;
			std::transform(sorted_word.begin(), sorted_word.end(), sorted_word.begin(), tolower);
			std::sort(sorted_word.begin(), sorted_word.end());

			if (compare == sorted_word) {
				ret.push_back(word);
			}
		}
		return ret;
	}
	return {};
}

TEST(GetAnagramsTest, ReturnsEmpty) {
	std::vector<std::string> expected;
	EXPECT_EQ(GetAnagrams("listen", {}), expected);
}

TEST(GetAnagramsTest, Returns1) {
	std::vector<std::string> expected{"listen"};
	EXPECT_EQ(GetAnagrams("listen", { "listen" }), expected);
}

TEST(GetAnagramsTest, Returns2) {
	std::vector<std::string> expected{ "inlets" };
	EXPECT_EQ(GetAnagrams("listen", { "inlets" }), expected);
}

TEST(GetAnagramsTest, Returns3) {
	std::vector<std::string> expected;
	EXPECT_EQ(GetAnagrams("listen", { "enlets" }), expected);
}

TEST(GetAnagramsTest, Returns4) {
	std::vector<std::string> expected{ "listen" };
	EXPECT_EQ(GetAnagrams("listen", { "listen", "enlets" , "banana" }), expected);
}

TEST(GetAnagramsTest, Returns5) {
	std::vector<std::string> expected{ "listen", "inlets" };
	EXPECT_EQ(GetAnagrams("listen", { "listen", "inlets" , "banana" }), expected);
}

TEST(GetAnagramsTest, Returns6) {
	std::vector<std::string> expected{ "InLets" };
	EXPECT_EQ(GetAnagrams("listen", { "InLets" }), expected);
}
