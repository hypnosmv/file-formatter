#include <gtest/gtest.h>

#include "formatters/FormatLooseParenthesis.hpp"


class FormatLooseParenthesisShould : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
protected:
    FormatLooseParenthesis sut_;
};

INSTANTIATE_TEST_CASE_P(FormatLooseParenthesisTests, FormatLooseParenthesisShould,
    ::testing::Values(
        std::make_tuple(" (", "(")
    ));

TEST_P(FormatLooseParenthesisShould, formatLooseParenthesis)
{
    std::string text = std::get<0>(GetParam());
    std::string expected = std::get<1>(GetParam());
    auto result = sut_.getFormatted(text);

    EXPECT_EQ(expected, result);
}
