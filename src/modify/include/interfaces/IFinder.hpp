#pragma once
#include <string>
#include <vector>


class Scope;

class IFinder
{
public:
    virtual ~IFinder() = default;
    virtual std::vector<Scope> getScopes(const std::string& text) const = 0;
};
