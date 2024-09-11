#pragma once
#include "common/ChainNode.hpp"
#include "interfaces/IFormatter.hpp"


class FormatScopeHandler : public ChainNode
{
public:
    FormatScopeHandler(std::shared_ptr<IFormatter> formatter);
    std::shared_ptr<WorkingData> handle(std::shared_ptr<WorkingData> data) const override;

private:
    std::shared_ptr<IFormatter> formatter_;
};
