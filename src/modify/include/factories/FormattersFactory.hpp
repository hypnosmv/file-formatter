#pragma once
#include <memory>
#include <string>

#include "interfaces/IFormatter.hpp"


class FormattersFactory
{
public:
    std::shared_ptr<IFormatter> createFormatter(const std::string& formatterName) const;
};
