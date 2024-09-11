#include <gtest/gtest.h>

#include "formatters/FormatSqueezedParenthesis.hpp"


class FormatSqueezedParenthesisShould : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
protected:
    FormatSqueezedParenthesis sut_;
};

INSTANTIATE_TEST_CASE_P(FormatSqueezedParenthesisTests, FormatSqueezedParenthesisShould,
    ::testing::Values(
        std::make_tuple("(", " (")
    ));

TEST_P(FormatSqueezedParenthesisShould, formatSqueezedParenthesis)
{
    std::string text = std::get<0>(GetParam());
    std::string expected = std::get<1>(GetParam());
    auto result = sut_.getFormatted(text);

    EXPECT_EQ(expected, result);
}
