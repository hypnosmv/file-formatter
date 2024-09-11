#pragma once
#include <string>


class IFormatter
{
public:
    virtual ~IFormatter() = default;
    virtual std::string getFormatted(const std::string_view data) const = 0;
};
