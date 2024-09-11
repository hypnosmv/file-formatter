#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Scope.hpp"


class IChainNode
{
public:
    struct WorkingData
    {
        std::string text;
        std::vector<Scope> scopes;
    };

    virtual ~IChainNode() = default;
    virtual std::shared_ptr<IChainNode> setNext(std::shared_ptr<IChainNode> next) = 0;
    virtual std::shared_ptr<WorkingData> handle(std::shared_ptr<WorkingData> data) const = 0;
};
