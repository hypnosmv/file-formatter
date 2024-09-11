#include <gtest/gtest.h>

#include "formatters/FormatTrailingBrace.hpp"


class FormatTrailingBraceShould : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
protected:
    FormatTrailingBrace sut_;
};

INSTANTIATE_TEST_CASE_P(FormatTrailingBraceTests, FormatTrailingBraceShould,
    ::testing::Values(
        std::make_tuple("a{\n",       "a\n{\n"),
        std::make_tuple("a{b}\n",     "a{b}\n"),
        std::make_tuple("a{b\r\n",    "a\r\n{\r\nb\r\n"),

        std::make_tuple(" a{\n",      " a\n {\n"),
        std::make_tuple("   a{\n",    "   a\n   {\n"),

        std::make_tuple("\ta{\n",     "\ta\n\t{\n"),
        std::make_tuple("\t\t\ta{\n", "\t\t\ta\n\t\t\t{\n"),

        std::make_tuple("a{b\n",      "a\n{\nb\n"),
        std::make_tuple(" a{b\n",     " a\n {\n  b\n"),
        std::make_tuple("  a{b\n",    "  a\n  {\n    b\n"),

        std::make_tuple(" a{ b\n",    " a\n {\n  b\n"),
        std::make_tuple("  a{   b\n", "  a\n  {\n    b\n")
    ));

TEST_P(FormatTrailingBraceShould, formatTrailingBrace)
{
    std::string text = std::get<0>(GetParam());
    std::string expected = std::get<1>(GetParam());
    auto result = sut_.getFormatted(text);

    EXPECT_EQ(expected, result);
}
