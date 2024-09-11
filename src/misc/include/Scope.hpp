#pragma once
#include <cstddef>


struct Scope
{
    Scope();
    Scope(size_t pos, size_t count);

    size_t pos;
    size_t count;

    bool includes(size_t pos) const;

    bool operator==(const Scope& other) const;
};
