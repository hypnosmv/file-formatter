#pragma once
#include "interfaces/IChainBuilder.hpp"
#include "interfaces/IChainNode.hpp"


class GuardedChainBuilder : public IChainBuilder
{
public:
    std::shared_ptr<IChainNode> getStartOfBuiltChain(
        const std::vector<IConfigInterpreter::Instruction>& config) const override;
};
