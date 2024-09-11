#include "formatters/FormatSqueezedParenthesis.hpp"


std::string FormatSqueezedParenthesis::getFormatted(const std::string_view text __attribute__((unused))) const
{
    return " (";
}
