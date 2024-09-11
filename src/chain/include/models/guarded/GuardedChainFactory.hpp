#pragma once
#include "interfaces/IChainFactory.hpp"
#include "models/guarded/GuardedConfigInterpreter.hpp"
#include "models/guarded/GuardedChainBuilder.hpp"


class GuardedChainFactory : public IChainFactory
{
public:
    std::shared_ptr<IConfigInterpreter> createConfigInterpreter() const override;
    std::shared_ptr<IChainBuilder> createChainBuilder() const override;
};
