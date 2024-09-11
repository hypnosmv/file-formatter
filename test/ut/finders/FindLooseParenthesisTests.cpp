#include <gtest/gtest.h>

#include "finders/FindLooseParenthesis.hpp"
#include "Scope.hpp"


class FindLooseParenthesisShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindLooseParenthesis sut_;
};

INSTANTIATE_TEST_CASE_P(FindLooseParenthesisTests, FindLooseParenthesisShould,
    ::testing::Values(
        std::make_tuple("a(",       std::vector<Scope>{}),
        std::make_tuple("a (",      std::vector<Scope>{{1, 2}}),
        std::make_tuple("a   (",    std::vector<Scope>{{1, 4}}),
        std::make_tuple("a\t(",     std::vector<Scope>{{1, 2}}),
        std::make_tuple("a\t\t\t(", std::vector<Scope>{{1, 4}}),

        std::make_tuple("if (",     std::vector<Scope>{}),
        std::make_tuple("for (",    std::vector<Scope>{}),
        std::make_tuple("while (",  std::vector<Scope>{}),
        std::make_tuple("switch (", std::vector<Scope>{}),

        std::make_tuple("aif (",    std::vector<Scope>{{3, 2}}),
        std::make_tuple("aif\t(",   std::vector<Scope>{{3, 2}}),
        std::make_tuple(" if (",    std::vector<Scope>{}),
        std::make_tuple("\tif\t(",  std::vector<Scope>{})
    ));

TEST_P(FindLooseParenthesisShould, findLooseParenthesis)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
