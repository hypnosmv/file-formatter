#include "Writer.hpp"


Writer::Writer(std::unique_ptr<IWriteStrategy>&& strategy)
    : strategy_(std::move(strategy))
{
}

Writer& Writer::operator=(Writer&& other)
{
    strategy_ = std::move(other.strategy_);
    return *this;
}

void Writer::setStrategy(std::unique_ptr<IWriteStrategy>&& strategy)
{
    strategy_ = std::move(strategy);
}

bool Writer::write(const std::string& path, const std::string& contents) const
{
    if (!strategy_) return false;
    return strategy_->write(path, contents);
}
