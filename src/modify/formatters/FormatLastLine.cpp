#include "formatters/FormatLastLine.hpp"


std::string FormatLastLine::getFormatted(const std::string_view text) const
{
    return text.empty() ? "" : std::string(text) + "\n";
}
