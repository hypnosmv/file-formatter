#pragma once
#include "interfaces/IFinder.hpp"


class FindLooseParenthesis : public IFinder
{
public:
    std::vector<Scope> getScopes(const std::string& text) const override;
};
