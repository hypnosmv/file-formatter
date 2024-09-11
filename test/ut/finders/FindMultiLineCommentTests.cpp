#include <gtest/gtest.h>

#include "finders/FindMultiLineComment.hpp"
#include "Scope.hpp"


class FindMultiLineCommentShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindMultiLineComment sut_;
};

INSTANTIATE_TEST_CASE_P(FindMultiLineCommentTests, FindMultiLineCommentShould,
    ::testing::Values(
        std::make_tuple("/*",               std::vector<Scope>{}),
        std::make_tuple("*/",               std::vector<Scope>{}),
        std::make_tuple("/*/",              std::vector<Scope>{}),
        std::make_tuple("/**/",             std::vector<Scope>{{0, 4}}),
        std::make_tuple("/*\n*/",           std::vector<Scope>{{0, 5}}),
        std::make_tuple(R"("/**/")",        std::vector<Scope>{{1, 4}}),
        std::make_tuple("a/*b*/c/**//*d*/", std::vector<Scope>{{1, 5}, {7, 4}, {11, 5}}),
        std::make_tuple("/***/",            std::vector<Scope>{{0, 5}}),
        std::make_tuple("/*/**/",           std::vector<Scope>{{0, 6}}),
        std::make_tuple("/**/*/",           std::vector<Scope>{{0, 4}})
    ));

TEST_P(FindMultiLineCommentShould, findMultiLineComment)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
