#include "finders/FindLooseParenthesis.hpp"
#include <string>
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindLooseParenthesis::getScopes(const std::string& text) const
{
    // Note: Lookbehind assertions are not supported in std::regex as of September 2024
    std::string basePattern(R"([ \t]+\()");
    std::regex actualPattern(basePattern);
    std::regex exceptionPattern(R"(\b(?:if|for|while|switch))" + basePattern);

    return utils::filterScopesByRestraints(
        utils::getRegexMatchedScopes(text, actualPattern),
        utils::getRegexMatchedScopes(text, exceptionPattern));
}
