#pragma once
#include "interfaces/IWriteStrategy.hpp"


class ToTextFile : public IWriteStrategy
{
public:
    bool write(const std::string& path, const std::string& contents) const override;
};
