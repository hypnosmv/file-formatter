#pragma once
#include <memory>

#include "interfaces/IReadStrategy.hpp"


class Reader
{
public:
    explicit Reader(std::unique_ptr<IReadStrategy>&& strategy = {});
    Reader& operator=(Reader&& other);

    void setStrategy(std::unique_ptr<IReadStrategy>&& strategy);
    std::optional<std::string> read(const std::string& path) const;

private:
    std::unique_ptr<IReadStrategy> strategy_;
};
