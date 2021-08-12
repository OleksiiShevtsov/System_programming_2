#include <gmock/gmock.h>
#include <algorithm>
#include <string>
#include <vector>

/*
if (?) "Sure."
if (!) "Whoa. chill out!"
if () "Fine. Be thar way!"
if (...) "Whatever"
*/

class Bob {
public:
	std::string ask(const std::string&);
};

std::string Bob::ask(const std::string& toApply) {
	if (std::string::npos != toApply.find('?')) {
		return "Sure.";
	}
	if (std::string::npos != toApply.find('!')) {
		return "Whoa. chill out!";
	}
	if ("" == toApply) {
		return "Fine. Be thar way!";
	}
	return "Whatever";
}

TEST(BobTest, BobAskSure) {
	Bob bob;
	EXPECT_EQ(bob.ask("Do you done your homework?"), "Sure.");
}

TEST(BobTest, BobAskWhoa) {
	Bob bob;
	EXPECT_EQ(bob.ask("What!!!"), "Whoa. chill out!");
}

TEST(BobTest, BobAskFine) {
	Bob bob;
	EXPECT_EQ(bob.ask(""), "Fine. Be thar way!");
}

TEST(BobTest, BobAskWhatever) {
	Bob bob;
	EXPECT_EQ(bob.ask("lol"), "Whatever");
}