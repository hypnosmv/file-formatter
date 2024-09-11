#include <gtest/gtest.h>

#include "finders/FindTrailingBrace.hpp"
#include "Scope.hpp"


class FindTrailingBraceShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindTrailingBrace sut_;
};

INSTANTIATE_TEST_CASE_P(FindTrailingBraceTests, FindTrailingBraceShould,
    ::testing::Values(
        std::make_tuple("{",                    std::vector<Scope>{}),
        std::make_tuple("\n{\n",                std::vector<Scope>{}),
        std::make_tuple("\r\n{\r\n",            std::vector<Scope>{}),

        std::make_tuple("a \t{a \t",            std::vector<Scope>{{0, 7}}),
        std::make_tuple("\na \t{a \t\n",        std::vector<Scope>{{1, 8}}),
        std::make_tuple("\r\na \t{a \t\r\n",    std::vector<Scope>{{2, 9}}),

        std::make_tuple("a{b\nc{d}e\nf{",       std::vector<Scope>{{0, 4}, {10, 2}}),
        std::make_tuple("a{b\r\nc{d}e\r\nf{",   std::vector<Scope>{{0, 5}, {12, 2}}),

        std::make_tuple("{}{}",                 std::vector<Scope>{}),
        std::make_tuple("{{}}",                 std::vector<Scope>{}),
        std::make_tuple("{{}{",                 std::vector<Scope>{{0, 4}}),

        std::make_tuple(" {",                   std::vector<Scope>{}),
        std::make_tuple("   {",                 std::vector<Scope>{}),
        std::make_tuple("\t{",                  std::vector<Scope>{}),
        std::make_tuple("\t\t\t{",              std::vector<Scope>{})
    ));

TEST_P(FindTrailingBraceShould, findTrailingBrace)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
