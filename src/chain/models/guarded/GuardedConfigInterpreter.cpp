#include "models/guarded/GuardedConfigInterpreter.hpp"
#include <list>

#include "Utils.hpp"
#include "ExitCode.hpp"
#include "models/guarded/GuardedType.hpp"


std::vector<IConfigInterpreter::Instruction> GuardedConfigInterpreter::makeInstructions(
    const std::string_view config) const
{
    std::vector<IConfigInterpreter::Instruction> instructions;

    size_t pos = 0;
    size_t lvl = 0;
    std::list<std::pair<size_t, std::string>> protectOrientedStack;
    while (pos < config.size())
    {
        char ch = config.at(pos);

        if (ch == '{') ++lvl;
        else if (ch == '}')
        {
            if (lvl > 0) --lvl;
            else std::exit(ExitCode::INVALID_CONFIG);

            while (protectOrientedStack.size() > 0 && protectOrientedStack.back().first > lvl)
            {
                protectOrientedStack.pop_back();
            }
        }
        else if (utils::isAlNumPunct(ch))
        {
            std::string expression = utils::readWhile(config, pos, utils::isAlNumPunct);
            std::vector<std::string> expressionParts = utils::splitStringBySeparator(expression, '.');

            switch (expressionParts.size())
            {
                case 1:
                    protectOrientedStack.emplace_back(lvl, expressionParts[0]);
                    break;
                case 2:
                    instructions.emplace_back(GuardedType::FindOriented, expressionParts[0]);

                    for (const auto& elem : protectOrientedStack)
                        instructions.emplace_back(GuardedType::ProtectOriented, elem.second);

                    instructions.emplace_back(GuardedType::FormatOriented, expressionParts[1]);
                    break;
                default:
                    std::exit(ExitCode::INVALID_CONFIG);
                    break;
            }
        }
        ++pos;
    }
    if (lvl != 0) std::exit(ExitCode::INVALID_CONFIG);

    return instructions;
}
