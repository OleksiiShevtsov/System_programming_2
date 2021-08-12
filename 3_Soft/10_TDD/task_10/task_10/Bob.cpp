#include <gmock/gmock.h>

class MyTest : public testing::Test
{
public:
    void SetUp()
    {
        my_i_ = 11;
        my_ptr_i_ = std::unique_ptr<int>(new int(10));
    }

    void TearDown()
    {
        my_ptr_i_.reset();
    }

protected:
    int my_i_ = 10;
    std::unique_ptr<int> my_ptr_i_ = nullptr;
};

TEST_F(MyTest, SetUpAndTearDownShowcase)
{
    EXPECT_EQ(my_i_, 11);
    EXPECT_EQ(*my_ptr_i_, 10);
}