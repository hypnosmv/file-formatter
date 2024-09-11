#include "handlers/FormatScopeHandler.hpp"

#include <algorithm>


FormatScopeHandler::FormatScopeHandler(std::shared_ptr<IFormatter> formatter)
    : formatter_(formatter)
{}

std::shared_ptr<IChainNode::WorkingData> FormatScopeHandler::handle(std::shared_ptr<IChainNode::WorkingData> data) const
{
    std::string formattedText;

    std::sort(data->scopes.begin(), data->scopes.end(), [](const Scope& lhs, const Scope& rhs)
        { return lhs.pos < rhs.pos; });

    size_t i = 0;
    size_t pos = 0;
    while (i < data->scopes.size() && pos < data->text.size())
    {
        std::string freeSection = data->text.substr(pos, data->scopes[i].pos - pos);
        formattedText += freeSection;

        std::string scopeSection = data->text.substr(data->scopes[i].pos, data->scopes[i].count);
        std::string formattedSection = formatter_->getFormatted(scopeSection);
        formattedText += formattedSection;

        ++i;
        pos += freeSection.size() + scopeSection.size();
    }

    if (pos < data->text.size())
    {
        formattedText += data->text.substr(pos);
    }

    data->text = formattedText;
    return ChainNode::handle(data);
}
