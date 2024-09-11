#include <gtest/gtest.h>

#include "finders/FindCharScope.hpp"
#include "Scope.hpp"


class FindCharScopeShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindCharScope sut_;
};

INSTANTIATE_TEST_CASE_P(FindCharScopeTests, FindCharScopeShould,
    ::testing::Values(
        std::make_tuple("'",                            std::vector<Scope>{}),
        std::make_tuple("''",                           std::vector<Scope>{{0, 2}}),
        std::make_tuple("'a",                           std::vector<Scope>{}),
        std::make_tuple("a'",                           std::vector<Scope>{}),
        std::make_tuple("'a'",                          std::vector<Scope>{{0, 3}}),

        std::make_tuple("' '",                          std::vector<Scope>{{0, 3}}),
        std::make_tuple("'  '",                         std::vector<Scope>{}),
        std::make_tuple("'   '",                        std::vector<Scope>{}),

        std::make_tuple("'\na'",                        std::vector<Scope>{}),
        std::make_tuple("'\r\na'",                      std::vector<Scope>{}),
        std::make_tuple("'a\n'",                        std::vector<Scope>{}),
        std::make_tuple("'a\r\n'",                      std::vector<Scope>{}),

        std::make_tuple("'\\\na'",                      std::vector<Scope>{{0, 5}}),
        std::make_tuple("'\\\r\na'",                    std::vector<Scope>{{0, 6}}),
        std::make_tuple("'a\\\n'",                      std::vector<Scope>{{0, 5}}),
        std::make_tuple("'a\\\r\n'",                    std::vector<Scope>{{0, 6}}),

        std::make_tuple("'\\\n\\\na\\\n\\\n'",          std::vector<Scope>{{0, 11}}),
        std::make_tuple("'\\\r\n\\\r\na\\\r\n\\\r\n'",  std::vector<Scope>{{0, 15}}),

        std::make_tuple("'a'b'c'",                      std::vector<Scope>{{0, 3}, {4, 3}}),
        std::make_tuple("'a'b'c",                       std::vector<Scope>{{0, 3}}),
        std::make_tuple("a'b'c'",                       std::vector<Scope>{{1, 3}}),

        std::make_tuple("'\t'",                         std::vector<Scope>{{0, 3}}),
        std::make_tuple("'\n'",                         std::vector<Scope>{}),
        std::make_tuple(R"('\')",                       std::vector<Scope>{}),

        std::make_tuple(R"('\'')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\"')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\?')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\\')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\a')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\b')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\f')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\n')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\r')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\t')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\v')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\!')",                      std::vector<Scope>{}),
        std::make_tuple(R"('\c')",                      std::vector<Scope>{}),
        std::make_tuple(R"('\B')",                      std::vector<Scope>{}),

        std::make_tuple(R"('\0')",                      std::vector<Scope>{{0, 4}}),
        std::make_tuple(R"('\12')",                     std::vector<Scope>{{0, 5}}),
        std::make_tuple(R"('\345')",                    std::vector<Scope>{{0, 6}}),
        std::make_tuple(R"('\1111')",                   std::vector<Scope>{}),
        std::make_tuple(R"('\78')",                     std::vector<Scope>{}),

        std::make_tuple(R"('\o{0}')",                   std::vector<Scope>{{0, 7}}),
        std::make_tuple(R"('\o{1234567}')",             std::vector<Scope>{{0, 13}}),
        std::make_tuple(R"('\o{78}')",                  std::vector<Scope>{}),

        std::make_tuple(R"('\x0')",                     std::vector<Scope>{{0, 5}}),
        std::make_tuple(R"('\x123456789ABCDEF')",       std::vector<Scope>{{0, 19}}),
        std::make_tuple(R"('\x123456789abcdef')",       std::vector<Scope>{{0, 19}}),
        std::make_tuple(R"('\x123456789aBcDef')",       std::vector<Scope>{{0, 19}}),
        std::make_tuple(R"('\xFG')",                    std::vector<Scope>{}),

        std::make_tuple(R"('\x{0}')",                   std::vector<Scope>{{0, 7}}),
        std::make_tuple(R"('\x{123456789ABCDEF}')",     std::vector<Scope>{{0, 21}}),
        std::make_tuple(R"('\x{123456789abcdef}')",     std::vector<Scope>{{0, 21}}),
        std::make_tuple(R"('\x{123456789aBcDef}')",     std::vector<Scope>{{0, 21}}),
        std::make_tuple(R"('\x{FG}')",                  std::vector<Scope>{}),

        std::make_tuple(R"('\u0000')",                  std::vector<Scope>{{0, 8}}),
        std::make_tuple(R"('\u0123')",                  std::vector<Scope>{{0, 8}}),
        std::make_tuple(R"('\u4567')",                  std::vector<Scope>{{0, 8}}),
        std::make_tuple(R"('\u89AB')",                  std::vector<Scope>{{0, 8}}),
        std::make_tuple(R"('\u89ab')",                  std::vector<Scope>{{0, 8}}),
        std::make_tuple(R"('\uCDEF')",                  std::vector<Scope>{{0, 8}}),
        std::make_tuple(R"('\ucDeF')",                  std::vector<Scope>{{0, 8}}),
        std::make_tuple(R"('\u100')",                   std::vector<Scope>{}),
        std::make_tuple(R"('\u10000')",                 std::vector<Scope>{}),
        std::make_tuple(R"('\u00FG')",                  std::vector<Scope>{}),

        std::make_tuple(R"('\u{0}')",                   std::vector<Scope>{{0, 7}}),
        std::make_tuple(R"('\u{123456789ABCDEF}')",     std::vector<Scope>{{0, 21}}),
        std::make_tuple(R"('\u{123456789abcdef}')",     std::vector<Scope>{{0, 21}}),
        std::make_tuple(R"('\u{123456789aBcDef}')",     std::vector<Scope>{{0, 21}}),
        std::make_tuple(R"('\u{FG}')",                  std::vector<Scope>{}),

        std::make_tuple(R"('\U01234567')",              std::vector<Scope>{{0, 12}}),
        std::make_tuple(R"('\U89ABCDEF')",              std::vector<Scope>{{0, 12}}),
        std::make_tuple(R"('\U89abcdef')",              std::vector<Scope>{{0, 12}}),
        std::make_tuple(R"('\U89abCdeF')",              std::vector<Scope>{{0, 12}}),
        std::make_tuple(R"('\U9ABCDEFG')",              std::vector<Scope>{}),
        std::make_tuple(R"('\U789ABCD')",               std::vector<Scope>{}),
        std::make_tuple(R"('\U789ABCDEF')",             std::vector<Scope>{})
    ));

TEST_P(FindCharScopeShould, findCharScope)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
