#include <gtest/gtest.h>

#include "finders/FindSingleLineComment.hpp"
#include "Scope.hpp"


class FindSingleLineCommentShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindSingleLineComment sut_;
};

INSTANTIATE_TEST_CASE_P(FindSingleLineCommentTests, FindSingleLineCommentShould,
    ::testing::Values(
        std::make_tuple("/a",                       std::vector<Scope>{}),
        std::make_tuple("//a",                      std::vector<Scope>{{0, 3}}),
        std::make_tuple("//a\nb",                   std::vector<Scope>{{0, 3}}),
        std::make_tuple("//a\r\nb",                 std::vector<Scope>{{0, 3}}),

        std::make_tuple("a/b",                      std::vector<Scope>{}),
        std::make_tuple("a//b",                     std::vector<Scope>{{1, 3}}),
        std::make_tuple("a//b\nc",                  std::vector<Scope>{{1, 3}}),
        std::make_tuple("a//b\r\nc",                std::vector<Scope>{{1, 3}}),

        std::make_tuple("ab//cde\nfgh//ij\n",       std::vector<Scope>{{2, 5}, {11, 4}}),
        std::make_tuple("a // bc\nde // f\n",       std::vector<Scope>{{2, 5}, {11, 4}}),

        std::make_tuple("\"//a\"",                  std::vector<Scope>{{1, 4}}),
        std::make_tuple("ab\"//cde\"\nfgh//ij\n",   std::vector<Scope>{{3, 6}, {13, 4}}),
        std::make_tuple("ab//cde\nfgh\"//ij\"\n",   std::vector<Scope>{{2, 5}, {12, 5}}),

        std::make_tuple("a///b",                    std::vector<Scope>{{1, 4}}),
        std::make_tuple("a////b",                   std::vector<Scope>{{1, 5}}),
        std::make_tuple("a/////b",                  std::vector<Scope>{{1, 6}}),

        std::make_tuple("a///b\n",                  std::vector<Scope>{{1, 4}}),
        std::make_tuple("a////b\n",                 std::vector<Scope>{{1, 5}}),
        std::make_tuple("a/////b\n",                std::vector<Scope>{{1, 6}})
    ));

TEST_P(FindSingleLineCommentShould, findSingleLineComment)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
