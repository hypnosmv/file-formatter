#include "finders/FindCharScope.hpp"
#include <string>
#include <regex>

#include "Utils.hpp"


std::vector<Scope> FindCharScope::getScopes(const std::string& text) const
{
    std::string singleQuote = "'";
    std::string matchLineContinuation = R"((?:\\\r?\n)*)";
    std::string nonCapturingGroupBegin = "(?:";
    std::string nonCapturingGroupEnd = ")?";
    std::string orMatch = "|";

    std::string almostAnything = R"([^\\\n])";
    std::string simpleEscapeSequence = R"(\\['"?\\abfnrtv])";
    std::string numericEscapeSequence1 = R"(\\[0-7]{1,3})";
    std::string numericEscapeSequence2 = R"(\\o\{[0-7]+\})";
    std::string numericEscapeSequence3 = R"(\\x[0-9a-fA-F]+)";
    std::string numericEscapeSequence4 = R"(\\x\{[0-9a-fA-F]+\})";
    std::string universalCharacterName1 = R"(\\u[0-9a-fA-F]{4})";
    std::string universalCharacterName2 = R"(\\u\{[0-9a-fA-F]+\})";
    std::string universalCharacterName3 = R"(\\U[0-9a-fA-F]{8})";

    std::regex pattern(
        singleQuote +
            matchLineContinuation +
                nonCapturingGroupBegin +
                    almostAnything + orMatch +
                    simpleEscapeSequence + orMatch +
                    numericEscapeSequence1 + orMatch +
                    numericEscapeSequence2 + orMatch +
                    numericEscapeSequence3 + orMatch +
                    numericEscapeSequence4 + orMatch +
                    universalCharacterName1 + orMatch +
                    universalCharacterName2 + orMatch +
                    universalCharacterName3 +
                nonCapturingGroupEnd +
            matchLineContinuation +
        singleQuote);

    return utils::getRegexMatchedScopes(text, pattern);
}
