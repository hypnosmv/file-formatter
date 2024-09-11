#pragma once
#include "interfaces/IConfigInterpreter.hpp"


class GuardedConfigInterpreter : public IConfigInterpreter
{
public:
    std::vector<Instruction> makeInstructions(const std::string_view config) const override;
};
