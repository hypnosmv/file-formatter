#pragma once
#include <memory>

#include "interfaces/IWriteStrategy.hpp"


class Writer
{
public:
    explicit Writer(std::unique_ptr<IWriteStrategy>&& strategy = {});
    Writer& operator=(Writer&& other);

    void setStrategy(std::unique_ptr<IWriteStrategy>&& strategy);
    bool write(const std::string& path, const std::string& contents) const;

private:
    std::unique_ptr<IWriteStrategy> strategy_;
};
