#include "Reader.hpp"


Reader::Reader(std::unique_ptr<IReadStrategy>&& strategy)
    : strategy_(std::move(strategy))
{
}

Reader& Reader::operator=(Reader&& other)
{
    strategy_ = std::move(other.strategy_);
    return *this;
}

void Reader::setStrategy(std::unique_ptr<IReadStrategy>&& strategy)
{
    strategy_ = std::move(strategy);
}

std::optional<std::string> Reader::read(const std::string& path) const
{
    if (!strategy_) return std::nullopt;
    return strategy_->read(path);
}
