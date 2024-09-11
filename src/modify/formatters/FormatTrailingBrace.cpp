#include "formatters/FormatTrailingBrace.hpp"
#include <vector>
#include <algorithm>

#include "Constants.hpp"
#include "Utils.hpp"


std::string FormatTrailingBrace::getFormatted(const std::string_view text) const
{
    std::string formattedText(text);

    size_t openBracePos = text.find_last_of('{');
    if (text.find_first_of('}', openBracePos + 1) != std::string_view::npos) return formattedText;

    auto endOfLineSequences = constants::END_OF_LINE_SEQUENCES;
    std::sort(endOfLineSequences.begin(),
              endOfLineSequences.end(),
              [](const auto& a, const auto& b) { return a.size() > b.size(); });

    std::string endOfLineSequence = "";
    for (const auto& eolSeq : endOfLineSequences)
    {
        if (text.ends_with(eolSeq))
        {
            endOfLineSequence = eolSeq;
            break;
        }
    }

    std::string indentation = utils::copyIndentation(text);
    formattedText.insert(openBracePos, endOfLineSequence + indentation);

    if (not formattedText.ends_with('{' + endOfLineSequence))
    {
        size_t currentlyFormattedPos = openBracePos + endOfLineSequence.size() + indentation.size() + 1;

        std::string subStrAfterOpenBrace = formattedText.substr(currentlyFormattedPos);
        utils::eraseIndentation(subStrAfterOpenBrace);

        formattedText.erase(currentlyFormattedPos);

        formattedText += endOfLineSequence + indentation + indentation + subStrAfterOpenBrace;
    }

    return formattedText;
}
