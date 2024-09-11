#pragma once
#include <string>
#include <vector>
#include <functional>
#include <regex>

#include "Scope.hpp"


namespace utils
{
    std::vector<Scope> findDuplicatedCharScopes(const std::string_view text, const char ch);
    std::vector<std::string> splitTextIntoLines(const std::string_view text);
    std::vector<std::string> splitStringBySeparator(std::string str, const char separator);
    std::string readWhile(const std::string_view text, size_t& pos, std::function<bool(char)> predicate);
    bool isAlNumPunct(const char ch);
    std::string copyIndentation(const std::string_view line);
    void eraseIndentation(std::string& line);
    std::vector<Scope> filterScopesByRestraints(const std::vector<Scope>& scopes, const std::vector<Scope>& restraints);
    std::vector<Scope> findString(const std::string_view text, const std::string_view str);

    std::vector<Scope> getRegexMatchedScopes(
        const std::string& text,
        const std::regex& pattern,
        std::function<Scope(const std::smatch&)> getScopeFromMatch =
            [](const std::smatch& match)
            {
                return Scope(static_cast<size_t>(match.position()), static_cast<size_t>(match.length()));
            });
}
