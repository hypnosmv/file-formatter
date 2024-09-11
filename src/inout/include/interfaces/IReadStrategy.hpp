#pragma once
#include <optional>
#include <string>


class IReadStrategy
{
public:
    virtual ~IReadStrategy() = default;
    virtual std::optional<std::string> read(const std::string& path) const = 0;
};
