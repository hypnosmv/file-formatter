#include <gtest/gtest.h>

#include "finders/FindStringScope.hpp"
#include "Scope.hpp"


class FindStringScopeShould : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Scope>>>
{
protected:
    FindStringScope sut_;
};

INSTANTIATE_TEST_CASE_P(FindStringScopeTests, FindStringScopeShould,
    ::testing::Values(
/* 0*/  std::make_tuple(R"(")",                             std::vector<Scope>{}),
/* 1*/  std::make_tuple(R"("")",                            std::vector<Scope>{{0, 2}}),
/* 2*/  std::make_tuple(R"("a)",                            std::vector<Scope>{}),
/* 3*/  std::make_tuple(R"(a")",                            std::vector<Scope>{}),
/* 4*/  std::make_tuple(R"("a")",                           std::vector<Scope>{{0, 3}}),

/* 5*/  std::make_tuple(R"(" ")",                           std::vector<Scope>{{0, 3}}),
/* 6*/  std::make_tuple(R"("  ")",                          std::vector<Scope>{{0, 4}}),
/* 7*/  std::make_tuple(R"("   ")",                         std::vector<Scope>{{0, 5}}),

/* 8*/  std::make_tuple("\"\na\"",                          std::vector<Scope>{}),
/* 9*/  std::make_tuple("\"\r\na\"",                        std::vector<Scope>{}),
/*10*/  std::make_tuple("\"a\n\"",                          std::vector<Scope>{}),
/*11*/  std::make_tuple("\"a\r\n\"",                        std::vector<Scope>{}),

/*12*/  std::make_tuple("\"\\\na\"",                        std::vector<Scope>{{0, 5}}),
/*13*/  std::make_tuple("\"\\\r\na\"",                      std::vector<Scope>{{0, 6}}),
/*14*/  std::make_tuple("\"a\\\n\"",                        std::vector<Scope>{{0, 5}}),
/*15*/  std::make_tuple("\"a\\\r\n\"",                      std::vector<Scope>{{0, 6}}),

/*16*/  std::make_tuple("\"\\\n\\\na\\\n\\\n\"",            std::vector<Scope>{{0, 11}}),
/*17*/  std::make_tuple("\"\\\r\n\\\r\na\\\r\n\\\r\n\"",    std::vector<Scope>{{0, 15}}),

/*18*/  std::make_tuple(R"("a"b"c")",                       std::vector<Scope>{{0, 3}, {4, 3}}),
/*19*/  std::make_tuple(R"("a"b"c)",                        std::vector<Scope>{{0, 3}}),
/*20*/  std::make_tuple(R"(a"b"c")",                        std::vector<Scope>{{1, 3}}),

/*21*/  std::make_tuple("\"\t\"",                           std::vector<Scope>{{0, 3}}),
/*22*/  std::make_tuple("\"\n\"",                           std::vector<Scope>{}),
/*23*/  std::make_tuple(R"("\")",                           std::vector<Scope>{}),

/*24*/  std::make_tuple(R"("\'")",                          std::vector<Scope>{{0, 4}}),
/*25*/  std::make_tuple(R"("\"")",                          std::vector<Scope>{{0, 4}}),
/*26*/  std::make_tuple(R"("\?")",                          std::vector<Scope>{{0, 4}}),
/*27*/  std::make_tuple(R"("\!")",                          std::vector<Scope>{{0, 4}}),
/*28*/  std::make_tuple(R"("\\")",                          std::vector<Scope>{{0, 4}}),
/*29*/  std::make_tuple(R"("\a")",                          std::vector<Scope>{{0, 4}}),
/*30*/  std::make_tuple(R"("\b")",                          std::vector<Scope>{{0, 4}}),
/*31*/  std::make_tuple(R"("\A")",                          std::vector<Scope>{{0, 4}}),
/*32*/  std::make_tuple(R"("\B")",                          std::vector<Scope>{{0, 4}}),
/*33*/  std::make_tuple(R"("\t")",                          std::vector<Scope>{{0, 4}}),
/*34*/  std::make_tuple(R"("\n")",                          std::vector<Scope>{{0, 4}}),

/*35*/  std::make_tuple(R"("'")",                           std::vector<Scope>{{0, 3}}),
/*36*/  std::make_tuple(R"(""")",                           std::vector<Scope>{{0, 2}}),

/*37*/  std::make_tuple(R"("abc"def"ghi")",                 std::vector<Scope>{{0, 5}, {8, 5}}),
/*38*/  std::make_tuple(R"("abc\"def"ghi")",                std::vector<Scope>{{0, 10}}),
/*39*/  std::make_tuple(R"("abc\\"def"ghi")",               std::vector<Scope>{{0, 7}, {10, 5}}),
/*40*/  std::make_tuple(R"("abc\\\"def"ghi")",              std::vector<Scope>{{0, 12}}),
/*41*/  std::make_tuple(R"("abc\\\"def\"ghi")",             std::vector<Scope>{{0, 17}})
    ));

TEST_P(FindStringScopeShould, findStringScope)
{
    std::string text = std::get<0>(GetParam());
    std::vector<Scope> expected = std::get<1>(GetParam());
    auto result = sut_.getScopes(text);

    EXPECT_EQ(expected, result);
}
