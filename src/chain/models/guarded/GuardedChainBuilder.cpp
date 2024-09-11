#include "models/guarded/GuardedChainBuilder.hpp"
#include "factories/FindersFactory.hpp"
#include "factories/FormattersFactory.hpp"
#include "handlers/FindScopeHandler.hpp"
#include "handlers/ProtectScopeHandler.hpp"
#include "handlers/FormatScopeHandler.hpp"
#include "models/guarded/GuardedType.hpp"


std::shared_ptr<IChainNode> GuardedChainBuilder::getStartOfBuiltChain(
    const std::vector<IConfigInterpreter::Instruction>& config) const
{
    FindersFactory findersFactory;
    FormattersFactory formattersFactory;

    std::shared_ptr<IChainNode> start = std::make_shared<ChainNode>();
    std::shared_ptr<IChainNode> node(start);
    for (size_t i = 0; i < config.size(); ++i)
    {
        std::shared_ptr<IChainNode> next;

        switch (config[i].type)
        {
            case GuardedType::FindOriented:
                next = std::make_shared<FindScopeHandler>(findersFactory.createFinder(config[i].subject));
                break;
            case GuardedType::ProtectOriented:
                next = std::make_shared<ProtectScopeHandler>(findersFactory.createFinder(config[i].subject));
                break;
            case GuardedType::FormatOriented:
                next = std::make_shared<FormatScopeHandler>(formattersFactory.createFormatter(config[i].subject));
                break;
        }

        node = node->setNext(next);
    }

    return start;
}
