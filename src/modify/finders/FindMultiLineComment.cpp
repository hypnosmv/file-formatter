#include "finders/FindMultiLineComment.hpp"
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindMultiLineComment::getScopes(const std::string& text) const
{
    std::regex pattern(R"(\/\*[^]*?\*\/)");

    return utils::getRegexMatchedScopes(text, pattern);
}
