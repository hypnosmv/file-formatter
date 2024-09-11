#include "Scope.hpp"


Scope::Scope()
    : pos(0)
    , count(0)
{
}

Scope::Scope(size_t pos, size_t count)
    : pos(pos)
    , count(count)
{
}

bool Scope::includes(size_t pos) const
{
    return pos >= this->pos && pos < this->pos + this->count;
}

bool Scope::operator==(const Scope& other) const
{
    return pos == other.pos && count == other.count;
}
