#include "handlers/FindScopeHandler.hpp"


FindScopeHandler::FindScopeHandler(std::shared_ptr<IFinder> finder)
    : finder_(finder)
{}

std::shared_ptr<IChainNode::WorkingData> FindScopeHandler::handle(std::shared_ptr<IChainNode::WorkingData> data) const
{
    data->scopes = finder_->getScopes(data->text);
    return ChainNode::handle(data);
}
