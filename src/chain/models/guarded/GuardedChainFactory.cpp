#include "models/guarded/GuardedChainFactory.hpp"


std::shared_ptr<IConfigInterpreter> GuardedChainFactory::createConfigInterpreter() const
{
    return std::make_shared<GuardedConfigInterpreter>();
}

std::shared_ptr<IChainBuilder> GuardedChainFactory::createChainBuilder() const
{
    return std::make_shared<GuardedChainBuilder>();
}
