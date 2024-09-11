#include "formatters/FormatLooseParenthesis.hpp"


std::string FormatLooseParenthesis::getFormatted(const std::string_view text __attribute__((unused))) const
{
    return "(";
}
