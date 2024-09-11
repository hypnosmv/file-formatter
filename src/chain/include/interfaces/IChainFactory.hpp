#pragma once
#include <memory>


class IConfigInterpreter;
class IChainBuilder;

class IChainFactory
{
public:
    virtual ~IChainFactory() = default;
    virtual std::shared_ptr<IConfigInterpreter> createConfigInterpreter() const = 0;
    virtual std::shared_ptr<IChainBuilder> createChainBuilder() const = 0;
};
