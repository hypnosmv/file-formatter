#pragma once
#include <memory>
#include <string>

#include "interfaces/IFinder.hpp"


class FindersFactory
{
public:
    std::shared_ptr<IFinder> createFinder(const std::string& finderName) const;
};
