#pragma once
#include <memory>

#include "interfaces/IChainNode.hpp"


class ChainNode : public IChainNode
{
public:
    std::shared_ptr<IChainNode> setNext(std::shared_ptr<IChainNode> next) override;
    std::shared_ptr<WorkingData> handle(std::shared_ptr<WorkingData> data) const override;

private:
    std::shared_ptr<IChainNode> next_;
};
