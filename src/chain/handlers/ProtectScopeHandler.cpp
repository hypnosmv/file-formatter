#include "handlers/ProtectScopeHandler.hpp"
#include "Utils.hpp"


ProtectScopeHandler::ProtectScopeHandler(std::shared_ptr<IFinder> finder)
    : finder_(finder)
{}

std::shared_ptr<IChainNode::WorkingData> ProtectScopeHandler::handle(std::shared_ptr<IChainNode::WorkingData> data) const
{
    data->scopes = utils::filterScopesByRestraints(data->scopes, finder_->getScopes(data->text));
    return ChainNode::handle(data);
}
