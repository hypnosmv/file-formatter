#pragma once
#include <vector>
#include <string>


class IConfigInterpreter
{
public:
    struct Instruction
    {
        unsigned type;
        std::string subject;
    };

    virtual ~IConfigInterpreter() = default;
    virtual std::vector<Instruction> makeInstructions(const std::string_view config) const = 0;
};
