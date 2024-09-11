#include <gtest/gtest.h>

#include "finders/FindTrailingSpace.hpp"
#include "Scope.hpp"


class FindTrailingSpaceShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindTrailingSpace sut_;
};

INSTANTIATE_TEST_CASE_P(FindTrailingSpaceTests, FindTrailingSpaceShould,
    ::testing::Values(
        std::make_tuple("a\n",              std::vector<Scope>{}),
        std::make_tuple("a \n",             std::vector<Scope>{{1, 1}}),
        std::make_tuple("a   \n",           std::vector<Scope>{{1, 3}}),
        std::make_tuple("a\t\n",            std::vector<Scope>{{1, 1}}),
        std::make_tuple("a\t\t\t\n",        std::vector<Scope>{{1, 3}}),

        std::make_tuple("a\r\n",            std::vector<Scope>{}),
        std::make_tuple("a \r\n",           std::vector<Scope>{{1, 1}}),
        std::make_tuple("a   \r\n",         std::vector<Scope>{{1, 3}}),
        std::make_tuple("a\t\r\n",          std::vector<Scope>{{1, 1}}),
        std::make_tuple("a\t\t\t\r\n",      std::vector<Scope>{{1, 3}}),

        std::make_tuple("\n",               std::vector<Scope>{}),
        std::make_tuple(" \n",              std::vector<Scope>{{0, 1}}),
        std::make_tuple("   \n",            std::vector<Scope>{{0, 3}}),
        std::make_tuple("\r\n",             std::vector<Scope>{}),
        std::make_tuple(" \r\n",            std::vector<Scope>{{0, 1}}),
        std::make_tuple("   \r\n",          std::vector<Scope>{{0, 3}}),

        std::make_tuple("abcdefg \n",       std::vector<Scope>{{7, 1}}),
        std::make_tuple("abcdefg   \n",     std::vector<Scope>{{7, 3}}),
        std::make_tuple("abc \nde  \n",     std::vector<Scope>{{3, 1}, {7, 2}}),
        std::make_tuple("a \nb  \nc   \n",  std::vector<Scope>{{1, 1}, {4, 2}, {8, 3}})
    ));

TEST_P(FindTrailingSpaceShould, findTrailingSpace)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
