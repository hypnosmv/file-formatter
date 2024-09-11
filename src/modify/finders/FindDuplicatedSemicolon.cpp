#include "finders/FindDuplicatedSemicolon.hpp"
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindDuplicatedSemicolon::getScopes(const std::string& text) const
{
    std::regex pattern(";{2,}");

    return utils::getRegexMatchedScopes(text, pattern);;
}
