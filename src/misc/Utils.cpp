#include "Utils.hpp"
#include "Constants.hpp"
#include "finders/FindStringScope.hpp"


namespace utils
{
    std::vector<Scope> findDuplicatedCharScopes(const std::string_view text, const char ch)
    {
        std::vector<Scope> scopes;

        std::string duplicatedChars{ch, ch};
        size_t pos = text.find(duplicatedChars);
        while (pos != std::string_view::npos)
        {
            size_t i = pos + 1;
            while (i + 1 < text.size() && text[i + 1] == ch) ++i;

            scopes.emplace_back(pos, i - pos + 1);
            pos = text.find(duplicatedChars, i + 1);
        }

        return scopes;
    }

    std::vector<std::string> splitTextIntoLines(const std::string_view text)
    {
        std::vector<std::string> lines;

        FindStringScope findStringScope;
        auto illScopes = findStringScope.getScopes(std::string(text.begin(), text.end()));
        size_t illIter = 0;

        size_t pos = 0;
        std::string carry;
        while (pos < text.size())
        {
            Scope nearestEof(std::string_view::npos, 0);
            for (const auto& eof : constants::END_OF_LINE_SEQUENCES)
            {
                size_t findEof = text.find(eof, pos);
                if (findEof < nearestEof.pos) nearestEof = Scope(findEof, eof.size());
            }

            if (illIter < illScopes.size() && illScopes[illIter].includes(nearestEof.pos))
            {
                carry += text.substr(pos, nearestEof.pos - pos + nearestEof.count);
                ++illIter;
            }
            else
            {
                lines.emplace_back(carry + std::string(text.substr(pos, nearestEof.pos - pos + nearestEof.count)));
                carry.clear();
            }

            pos = nearestEof.pos + nearestEof.count;
        }

        return lines;
    }

    std::vector<std::string> splitStringBySeparator(std::string str, const char separator)
    {
        if (str.empty()) return {};
        if (str.front() != separator) str.insert(str.begin(), separator);
        if (str.back() != separator) str += separator;

        std::vector<std::string> result;

        size_t beginSeparator = 0;
        size_t endSeparator = str.find_first_of(separator, 1);
        while (endSeparator != std::string::npos)
        {
            result.emplace_back(str.substr(beginSeparator + 1, endSeparator - beginSeparator - 1));
            beginSeparator = endSeparator;
            endSeparator = str.find_first_of(separator, beginSeparator + 1);
        }

        return result;
    }

    std::string readWhile(const std::string_view text, size_t& pos, std::function<bool(char)> predicate)
    {
        std::string result;
        while (pos < text.size() && predicate(text[pos])) result += text[pos++];
        return result;
    }

    bool isAlNumPunct(const char ch)
    {
        return std::isalnum(ch) || std::ispunct(ch);
    }

    std::string copyIndentation(const std::string_view line)
    {
        std::string indentation;
        for (char ch : line)
        {
            if (std::find(constants::INDENTATION_SEQUENCES.begin(),
                          constants::INDENTATION_SEQUENCES.end(),
                          std::string{ch}) != constants::INDENTATION_SEQUENCES.end())
            {
                indentation += ch;
            }
            else break;
        }
        return indentation;
    }

    void eraseIndentation(std::string& line)
    {
        line.erase(0, copyIndentation(line).size());
    }

    std::vector<Scope> filterScopesByRestraints(const std::vector<Scope>& scopes, const std::vector<Scope>& restraints)
    {
        std::vector<Scope> filteredScopes;

        size_t i = 0;
        size_t j = 0;
        while (i < scopes.size() && j < restraints.size())
        {
            size_t dataScopeFirstChPos = scopes[i].pos;
            size_t dataScopeLastChPos = scopes[i].pos + scopes[i].count - 1;

            size_t protectedScopeFirstChPos = restraints[j].pos;
            size_t protectedScopeLastChPos = restraints[j].pos + restraints[j].count - 1;

            if (dataScopeFirstChPos > protectedScopeLastChPos)
            {
                ++j;
                continue;
            }

            if (!(restraints[j].includes(dataScopeFirstChPos) || restraints[j].includes(dataScopeLastChPos)
                || scopes[i].includes(protectedScopeFirstChPos) || scopes[i].includes(protectedScopeLastChPos)))
            {
                filteredScopes.push_back(scopes[i]);
            }

            ++i;
        }

        while (i < scopes.size()) filteredScopes.push_back(scopes[i++]);

        return filteredScopes;
    }

    std::vector<Scope> findString(const std::string_view text, const std::string_view str)
    {
        std::vector<Scope> scopes;

        size_t pos = text.find(str);
        while (pos != std::string_view::npos)
        {
            scopes.emplace_back(pos, str.size());
            pos = text.find(str, pos + str.size());
        }

        return scopes;
    }

    std::vector<Scope> getRegexMatchedScopes(
        const std::string& text,
        const std::regex& pattern,
        std::function<Scope(const std::smatch&)> getScopeFromMatch)
    {
        std::vector<Scope> scopes;

        for (auto it = std::sregex_iterator(text.begin(), text.end(), pattern); it != std::sregex_iterator(); ++it)
        {
            std::smatch match = *it;
            scopes.push_back(getScopeFromMatch(match));
        }

        return scopes;
    }
}
