#include <gtest/gtest.h>

#include "finders/FindDuplicatedSemicolon.hpp"
#include "Scope.hpp"


class FindDuplicatedSemicolonShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindDuplicatedSemicolon sut_;
};

INSTANTIATE_TEST_CASE_P(FindDuplicatedSemicolonTests, FindDuplicatedSemicolonShould,
    ::testing::Values(
        std::make_tuple("abcdef",       std::vector<Scope>{}),
        std::make_tuple(";;\n",         std::vector<Scope>{{0, 2}}),
        std::make_tuple(";;\n;;\n",     std::vector<Scope>{{0, 2}, {3, 2}}),
        std::make_tuple("abc;;;;cde",   std::vector<Scope>{{3, 4}})
    ));

TEST_P(FindDuplicatedSemicolonShould, findDuplicatedSemicolon)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
