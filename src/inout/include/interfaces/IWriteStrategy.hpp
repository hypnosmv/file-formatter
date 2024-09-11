#pragma once
#include <string>


class IWriteStrategy
{
public:
    virtual ~IWriteStrategy() = default;
    virtual bool write(const std::string& path, const std::string& contents) const = 0;
};
