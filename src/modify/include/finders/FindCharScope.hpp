#pragma once
#include "interfaces/IFinder.hpp"


class FindCharScope : public IFinder
{
public:
    std::vector<Scope> getScopes(const std::string& text) const override;
};
