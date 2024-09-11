#pragma once
#include <memory>
#include <vector>

#include "interfaces/IConfigInterpreter.hpp"


class IChainNode;

class IChainBuilder
{
public:
    virtual ~IChainBuilder() = default;
    virtual std::shared_ptr<IChainNode> getStartOfBuiltChain(
        const std::vector<IConfigInterpreter::Instruction>& config) const = 0;
};
