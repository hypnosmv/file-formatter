#include "finders/FindSingleLineComment.hpp"
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindSingleLineComment::getScopes(const std::string& text) const
{
    std::regex pattern(R"(\/\/.*)");

    return utils::getRegexMatchedScopes(text, pattern);
}
