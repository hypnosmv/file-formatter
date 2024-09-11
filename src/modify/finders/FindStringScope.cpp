#include "finders/FindStringScope.hpp"
#include <string>
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindStringScope::getScopes(const std::string& text) const
{
    std::string quotationMark = R"(")";
    std::string matchLineContinuation = R"((?:\\\r?\n)*)";
    std::string nonCapturingGroupBegin = "(?:";
    std::string nonCapturingGroupEnd = ")*?";
    std::string orMatch = "|";

    std::string almostAnything = R"([^\\\n])";
    std::string anyEscapeSequence = R"(\\[^])";

    std::regex pattern(
        quotationMark +
            matchLineContinuation +
                nonCapturingGroupBegin +
                    almostAnything + orMatch +
                    anyEscapeSequence +
                nonCapturingGroupEnd +
            matchLineContinuation +
        quotationMark);

    return utils::getRegexMatchedScopes(text, pattern);
}
