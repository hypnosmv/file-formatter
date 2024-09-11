#pragma once
#include "interfaces/IFormatter.hpp"


class FormatLooseParenthesis : public IFormatter
{
public:
    std::string getFormatted(const std::string_view text) const override;
};
