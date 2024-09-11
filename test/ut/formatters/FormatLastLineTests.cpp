#include <gtest/gtest.h>

#include "formatters/FormatLastLine.hpp"


class FormatLastLineShould : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
protected:
    FormatLastLine sut_;
};

INSTANTIATE_TEST_CASE_P(FormatLastLineTests, FormatLastLineShould,
    ::testing::Values(
        std::make_tuple("",     ""),
        std::make_tuple("a",    "a\n"),
        std::make_tuple("abc",  "abc\n")
    ));

TEST_P(FormatLastLineShould, formatLastLine)
{
    std::string text = std::get<0>(GetParam());
    std::string expected = std::get<1>(GetParam());
    auto result = sut_.getFormatted(text);

    EXPECT_EQ(expected, result);
}
