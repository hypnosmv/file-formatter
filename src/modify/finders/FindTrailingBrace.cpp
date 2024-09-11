#include "finders/FindTrailingBrace.hpp"
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindTrailingBrace::getScopes(const std::string& text) const
{
    std::regex pattern(R"(.*\S+.*\{[^\}\n]*(?:\n|$))");

    return utils::getRegexMatchedScopes(text, pattern);
}
