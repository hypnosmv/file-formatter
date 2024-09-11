#include "factories/FormattersFactory.hpp"
#include "ExitCode.hpp"
#include "formatters/FormatDuplicatedSemicolon.hpp"
#include "formatters/FormatLastLine.hpp"
#include "formatters/FormatLooseParenthesis.hpp"
#include "formatters/FormatSqueezedParenthesis.hpp"
#include "formatters/FormatTrailingBrace.hpp"
#include "formatters/FormatTrailingSpace.hpp"


std::shared_ptr<IFormatter> FormattersFactory::createFormatter(const std::string& formatterName) const
{
    if (formatterName == "FORMAT_DUPLICATED_SEMICOLON") return std::make_shared<FormatDuplicatedSemicolon>();
    else if (formatterName == "FORMAT_LAST_LINE") return std::make_shared<FormatLastLine>();
    else if (formatterName == "FORMAT_LOOSE_PARENTHESIS") return std::make_shared<FormatLooseParenthesis>();
    else if (formatterName == "FORMAT_SQUEEZED_PARENTHESIS") return std::make_shared<FormatSqueezedParenthesis>();
    else if (formatterName == "FORMAT_TRAILING_BRACE") return std::make_shared<FormatTrailingBrace>();
    else if (formatterName == "FORMAT_TRAILING_SPACE") return std::make_shared<FormatTrailingSpace>();
    else std::exit(ExitCode::INVALID_FORMATTER_NAME);
}
