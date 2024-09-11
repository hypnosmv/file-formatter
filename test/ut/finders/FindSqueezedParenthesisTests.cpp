#include <gtest/gtest.h>

#include "finders/FindSqueezedParenthesis.hpp"
#include "Scope.hpp"


class FindSqueezedParenthesisShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindSqueezedParenthesis sut_;
};

INSTANTIATE_TEST_CASE_P(FindSqueezedParenthesisTests, FindSqueezedParenthesisShould,
    ::testing::Values(
        std::make_tuple("if(abc)",      std::vector<Scope>{{2, 1}}),
        std::make_tuple("else if(abc)", std::vector<Scope>{{7, 1}}),
        std::make_tuple("while(abc)",   std::vector<Scope>{{5, 1}}),
        std::make_tuple("for(abc)",     std::vector<Scope>{{3, 1}}),
        std::make_tuple("switch(abc)",  std::vector<Scope>{{6, 1}}),
        std::make_tuple("abc(def)",     std::vector<Scope>{}),
        std::make_tuple("if",           std::vector<Scope>{}),
        std::make_tuple("if (abc)",     std::vector<Scope>{})
    ));

TEST_P(FindSqueezedParenthesisShould, findSqueezedParenthesis)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
