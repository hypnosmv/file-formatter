#include "finders/FindLastLine.hpp"
#include <regex>
#include <functional>

#include "Utils.hpp"


std::vector<Scope> FindLastLine::getScopes(const std::string& text) const
{
    std::regex pattern("\n.+$");

    std::function<Scope(const std::smatch&)> getScopeFromMatch =
        [](const std::smatch& match)
        {
            return Scope(static_cast<size_t>(match.position() + 1), static_cast<size_t>(match.length() - 1));
        };

    return utils::getRegexMatchedScopes(text, pattern, getScopeFromMatch);
}
