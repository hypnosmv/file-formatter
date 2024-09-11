#include <gtest/gtest.h>

#include "formatters/FormatDuplicatedSemicolon.hpp"


class FormatDuplicatedSemicolonShould : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
protected:
    FormatDuplicatedSemicolon sut_;
};

INSTANTIATE_TEST_CASE_P(FormatDuplicatedSemicolonTests, FormatDuplicatedSemicolonShould,
    ::testing::Values(
        std::make_tuple(";;",   ";"),
        std::make_tuple(";;;",  ";"),
        std::make_tuple(";;;;", ";")
    ));

TEST_P(FormatDuplicatedSemicolonShould, formatDuplicatedSemicolon)
{
    std::string text = std::get<0>(GetParam());
    std::string expected = std::get<1>(GetParam());
    auto result = sut_.getFormatted(text);

    EXPECT_EQ(expected, result);
}
