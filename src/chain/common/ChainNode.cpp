#include "common/ChainNode.hpp"


std::shared_ptr<IChainNode> ChainNode::setNext(std::shared_ptr<IChainNode> next)
{
    next_ = next;
    return next_;
}

std::shared_ptr<IChainNode::WorkingData> ChainNode::handle(std::shared_ptr<IChainNode::WorkingData> data) const
{
    if (next_) return this->next_->handle(data);
    return data;
}
