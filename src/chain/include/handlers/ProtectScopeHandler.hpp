#pragma once
#include "common/ChainNode.hpp"
#include "interfaces/IFinder.hpp"


class ProtectScopeHandler : public ChainNode
{
public:
    ProtectScopeHandler(std::shared_ptr<IFinder> finder);
    std::shared_ptr<WorkingData> handle(std::shared_ptr<WorkingData> data) const override;

private:
    std::shared_ptr<IFinder> finder_;
};
