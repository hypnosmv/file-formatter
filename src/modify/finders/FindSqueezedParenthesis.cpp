#include "finders/FindSqueezedParenthesis.hpp"
#include <regex>
#include <functional>

#include "Scope.hpp"
#include "Utils.hpp"


std::vector<Scope> FindSqueezedParenthesis::getScopes(const std::string& text) const
{
    std::regex pattern(R"(\b(?:if|for|while|switch)\()");

    std::function<Scope(const std::smatch&)> getScopeFromMatch =
        [](const std::smatch& match)
        {
            return Scope(static_cast<size_t>(match.position() + match.length() - 1), 1u);
        };

    return utils::getRegexMatchedScopes(text, pattern, getScopeFromMatch);
}
