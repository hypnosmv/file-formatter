#pragma once
#include "interfaces/IReadStrategy.hpp"


class FromTextFile : public IReadStrategy
{
public:
    std::optional<std::string> read(const std::string& path) const override;
};
