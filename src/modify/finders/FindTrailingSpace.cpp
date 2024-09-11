#include "finders/FindTrailingSpace.hpp"
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindTrailingSpace::getScopes(const std::string& text) const
{
    std::regex pattern(R"((?: |\t)+(?=\n|\r\n))");

    return utils::getRegexMatchedScopes(text, pattern);
}
