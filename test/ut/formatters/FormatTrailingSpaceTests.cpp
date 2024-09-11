#include <gtest/gtest.h>

#include "formatters/FormatTrailingSpace.hpp"


class FormatTrailingSpaceShould : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
protected:
    FormatTrailingSpace sut_;
};

INSTANTIATE_TEST_CASE_P(FormatTrailingSpaceTests, FormatTrailingSpaceShould,
    ::testing::Values(
        std::make_tuple(" ",    ""),
        std::make_tuple("  ",   ""),
        std::make_tuple("   ",  "")
    ));

TEST_P(FormatTrailingSpaceShould, formatTrailingSpace)
{
    std::string text = std::get<0>(GetParam());
    std::string expected = std::get<1>(GetParam());
    auto result = sut_.getFormatted(text);

    EXPECT_EQ(expected, result);
}
