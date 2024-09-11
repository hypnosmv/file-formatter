#include <gtest/gtest.h>

#include "finders/FindLastLine.hpp"
#include "Scope.hpp"


class FindLastLineShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindLastLine sut_;
};

INSTANTIATE_TEST_CASE_P(FindLastLineTests, FindLastLineShould,
    ::testing::Values(
        std::make_tuple("\n",               std::vector<Scope>{}),
        std::make_tuple("\n\n",             std::vector<Scope>{}),
        std::make_tuple("\n\n\n",           std::vector<Scope>{}),
        std::make_tuple("a\nb",             std::vector<Scope>{{2, 1}}),
        std::make_tuple("\na\nb",           std::vector<Scope>{{3, 1}}),
        std::make_tuple("\nabc\ndef",       std::vector<Scope>{{5, 3}}),

        std::make_tuple("\r\n",             std::vector<Scope>{}),
        std::make_tuple("\r\n\r\n",         std::vector<Scope>{}),
        std::make_tuple("\r\n\r\n\r\n",     std::vector<Scope>{}),
        std::make_tuple("a\r\nb",           std::vector<Scope>{{3, 1}}),
        std::make_tuple("\r\na\r\nb",       std::vector<Scope>{{5, 1}}),
        std::make_tuple("\r\nabc\r\ndef",   std::vector<Scope>{{7, 3}})
    ));

TEST_P(FindLastLineShould,findLastLine)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
