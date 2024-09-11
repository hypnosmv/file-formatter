#pragma once
#include "interfaces/IFinder.hpp"


class FindStringScope : public IFinder
{
public:
    std::vector<Scope> getScopes(const std::string& text) const override;
};
